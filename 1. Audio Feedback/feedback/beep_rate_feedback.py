from feedback.feedback import FeedbackMechanism
from config import Config
import pygame
from kivy.clock import Clock

class BeepRateFeedback(FeedbackMechanism):
    def __init__(self):
        # Load the beep sound
        self.beep_sound = pygame.mixer.Sound(str(Config.BEEP_SOUND_PATH))
        self.current_interval = None
        self.beep_event = None

    def give_feedback(self, normalized_distance, **kwargs):
        # Determine the beep interval based on normalized_distance
        # Closer distance means shorter interval (more frequent beeps)
        min_interval = Config.MIN_BEEP_INTERVAL
        max_interval = Config.MAX_BEEP_INTERVAL

        # Invert the normalized distance for mapping
        proximity = 1 - normalized_distance  # Closer distance gives higher proximity

        # Calculate the interval
        interval = max_interval - (max_interval - min_interval) * proximity

        # If the interval has changed significantly, reschedule the beeps
        if self.current_interval is None or abs(interval - self.current_interval) > 0.1:
            self.current_interval = interval
            self._schedule_beeps()

    def _schedule_beeps(self):
        # Cancel any existing beep events
        if self.beep_event:
            self.beep_event.cancel()

        # Schedule the beep sound to play at the current interval
        self.beep_event = Clock.schedule_interval(self._play_beep, self.current_interval)

    def _play_beep(self, dt):
        self.beep_sound.play()

    def reset(self):
        # Cancel any scheduled beeps
        if self.beep_event:
            self.beep_event.cancel()
            self.beep_event = None
        self.current_interval = None