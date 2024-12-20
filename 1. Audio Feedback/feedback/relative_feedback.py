from feedback.feedback import FeedbackMechanism
from config import Config
import pygame

class RelativeFeedback(FeedbackMechanism):
    def __init__(self):
        # Load the sound files for positive and negative feedback
        self.positive_sound = pygame.mixer.Sound(str(Config.POSITIVE_SOUND_PATH))
        self.negative_sound = pygame.mixer.Sound(str(Config.NEGATIVE_SOUND_PATH))
        self.previous_distance = None  # To store the previous distance

    def give_feedback(self, normalized_distance, player_x, player_y, target_x, target_y, **kwargs):
        # Calculate the current distance
        current_distance = ((player_x - target_x) ** 2 + (player_y - target_y) ** 2) ** 0.5

        # If this is the first move, there is no previous distance to compare
        if self.previous_distance is None:
            self.previous_distance = current_distance
            return

        if current_distance < self.previous_distance:
            # Player is getting closer
            self.positive_sound.play()
        else:
            # Player is moving away or staying the same
            self.negative_sound.play()

        # Update the previous distance
        self.previous_distance = current_distance