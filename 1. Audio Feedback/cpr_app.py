import numpy as np
import random
import time
import pygame
from pathlib import Path

from kivy.lang import Builder
from kivy.uix.screenmanager import Screen
from kivymd.uix.dialog import MDDialog
from kivymd.uix.button import MDFlatButton
from kivy.properties import NumericProperty, StringProperty
from kivymd.app import MDApp
from kivy.core.audio import SoundLoader
from kivy.clock import Clock


from config import Config
from models.custom_toggle_button import CustomToggleButton
from models.game_statistics import GameStatistics
from models.clickable_grid import ClickableGrid
from feedback.pitch_feedback import PitchFeedback
from feedback.volume_feedback import VolumeFeedback
from feedback.directional_feedback import DirectionalFeedback
from feedback.relative_feedback import RelativeFeedback
from feedback.beep_rate_feedback import BeepRateFeedback



# Initialize pygame mixer
pygame.mixer.init()


class StartScreen(Screen):
    pass


class GameScreen(Screen):
    pass


class CPRApp(MDApp):
    x_value = NumericProperty(0)
    y_value = NumericProperty(0)
    distance_to_correct = NumericProperty(0)
    correct_x = NumericProperty(0)  # Set the correct x position
    correct_y = NumericProperty(0)  # Set the correct y position
    number_of_levels = len(Config.GRID_SIZES)
    current_level = NumericProperty(1)  # Start at level 1
    current_columns = NumericProperty(0)
    current_rows = NumericProperty(0)
    clicks = NumericProperty(0)
    time_elapsed = NumericProperty(0)
    timer_event = None
    start_time = None

    level_stats = []  # List to store stats for each level

    feedback_mode = StringProperty('pitch')  # Default value is 'pitch'


    def __init__(self, **kwargs):
            super().__init__(**kwargs)
            self.game_statistics = GameStatistics()


    def build(self):
        self.sound = None
        self.beep_sound = SoundLoader.load(str(Config.BEEP_SOUND_PATH))
        self.correct_sound = SoundLoader.load(str(Config.CORRECT_SOUND_PATH))

         # Load the other KV files first
        self.load_other_kv_files()
        
        # Load cpr_app.kv and set self.root to the root widget
        self.root = self.load_root_kv()
        
        return self.root
    

    def load_other_kv_files(self):
        kv_dir = Path(__file__).parent / 'kv'
        kv_files = ['custom_widgets.kv', 'start_screen.kv', 'game_screen.kv']
        for kv_filename in kv_files:
            kv_file = kv_dir / kv_filename
            print(f"Loading KV file: {kv_file}")
            Builder.load_file(str(kv_file))


    def load_root_kv(self):
        kv_dir = Path(__file__).parent / 'kv'
        kv_file = kv_dir / 'cpr_app.kv'
        print(f"Loading root KV file: {kv_file}")
        return Builder.load_file(str(kv_file))

    
    def start_game(self):
        feedback_classes = {
            'pitch': PitchFeedback,
            'volume': VolumeFeedback,
            'directional': DirectionalFeedback,
            'relative': RelativeFeedback,
            'beep_rate': BeepRateFeedback
        }
        self.feedback_mechanism = feedback_classes[self.feedback_mode]()
        # Transition to the game screen
        self.root.current = 'game_screen'
        self.start_level()


    def start_level(self):
        """Initialize a new level with updated grid size and reset metrics."""

        self.current_columns, self.current_rows = Config.GRID_SIZES[self.current_level]
        
        self.correct_x = random.randrange(0, self.current_columns, 1)
        self.correct_y = random.randrange(0, self.current_rows, 1)

        self.clicks = 0  # Reset click count
        self.time_elapsed = 0  # Reset time
        self.start_time = time.time()  # Start the timer

         # Reset previous distance in feedback mechanism if it has that attribute
        if hasattr(self.feedback_mechanism, 'previous_distance'):
            self.feedback_mechanism.previous_distance = None
            
        # Start updating the elapsed time
        if self.timer_event:
            self.timer_event.cancel()  # Cancel any existing timer
        self.timer_event = Clock.schedule_interval(self.update_time_elapsed, 1.0)

        # Recreate grid with new size
        self.root.get_screen('game_screen').ids.clickable_grid.create_grid()


    def update_position(self, x, y):
        # Update x, y coordinates based on grid clicks
        self.x_value = x
        self.y_value = y
        self.clicks += 1  # Increment click count
        self.check_proximity()
        self.give_feedback()


    def check_proximity(self):
        # Calculate the distance to the correct position
        self.distance_to_correct = float(np.sqrt((self.x_value - self.correct_x) ** 2 + (self.y_value - self.correct_y) ** 2))
        # Adjust sound properties based on proximity
        max_distance = float(np.sqrt((self.current_columns- 1) ** 2 + (self.current_rows - 1) ** 2))
        self.normalized_distance = min(self.distance_to_correct / max_distance, 1.0) 
    
    
    def give_feedback(self):
        # Use the feedback mechanism instance
        self.feedback_mechanism.give_feedback(
            normalized_distance=self.normalized_distance,
            player_x=self.x_value,
            player_y=self.y_value,
            target_x=self.correct_x,
            target_y=self.correct_y,
            max_x=self.current_columns,
            max_y=self.current_rows
        )

        # Check if the user clicked the correct square
        if self.distance_to_correct == 0:
            print("You won!")
            self.level_complete()


    def update_time_elapsed(self, dt):
        """Update the elapsed time during gameplay."""
        self.time_elapsed = round(time.time() - self.start_time, 2)


    def level_complete(self):
        """Handle the completion of a level."""
        # Stop the timer
        if self.timer_event:
            self.timer_event.cancel()
            self.timer_event = None
        
        # Reset the feedback mechanism
        if self.feedback_mode == 'beep_rate':
            self.feedback_mechanism.reset()

        self.time_elapsed = round(time.time() - self.start_time, 2)  # Stop the timer
        self.correct_sound.play()

        # Update total statistics
        self.game_statistics.add_level_stat(
            level=self.current_level,
            time=self.time_elapsed,
            clicks=self.clicks,
            feedback_method=self.feedback_mode
        )

        print(f"Level {self.current_level} Complete! Time: {self.time_elapsed} sec, Clicks: {self.clicks}")

        if self.current_level < len(Config.GRID_SIZES):
            self.current_level += 1  # Move to the next level
            self.start_level()  # Start the next level
        else:
            print("Game Over! You've completed all levels.")
            self.end_game()


    def end_game(self):
        """Show game summary"""
        stats_text = "Congratulations! You've completed all levels!\n\n"

        # Export the data 
        self.game_statistics.write_to_csv()

        for stat in self.game_statistics.level_stats:
            stats_text += (
                f"Level {stat['level']} - Time: {stat['time']} sec, "
                f"Clicks: {stat['clicks']}\n"
            )

        # Create a dialog to display the statistics
        self.dialog = MDDialog(
            title="Game Over",
            text=stats_text,
            size_hint=(0.8, None),
            height="400dp",
            auto_dismiss=False,  # Prevent dismissing by clicking outside
            buttons=[
                MDFlatButton(
                    text="OK",
                    on_release=lambda x: self.reset_game()
                ),
            ],
        )
        self.dialog.open()
    

    def reset_game(self):
        # Reset game variables
        self.current_level = 1
        self.game_statistics.reset() # Reset statistics
        self.dialog.dismiss()
        self.root.current = 'start_screen'