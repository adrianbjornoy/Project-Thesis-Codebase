import pygame
import numpy as np

from feedback.feedback import FeedbackMechanism
from config import Config


class VolumeFeedback(FeedbackMechanism):
    def __init__(self):
        self.sound = None

    def give_feedback(self, normalized_distance, player_x, player_y, target_x, target_y, max_x, max_y):
        volume = max(0, (1.0 - normalized_distance))
        self.play_frequency(frequency=1000, volume=volume)

    def play_frequency(self, frequency, volume):
        # Stop the previous sound if it's still playing
        if self.sound:
            self.sound.stop()

        # Generate a new sound with the calculated frequency
        sample_rate = 44100
        duration = 0.3  # In seconds
        amplitude = 4096

        # Generate sound wave data for the given frequency
        wave = np.sin(2 * np.pi * np.arange(sample_rate * duration) * frequency / sample_rate).astype(np.float32)

        # Create a sound object from the wave data
        sound_array = np.array([wave, wave]).T * amplitude
        sound_bytes = sound_array.astype(np.int16).tobytes()

        # Load the sound into pygame
        self.sound = pygame.mixer.Sound(buffer=sound_bytes)
        self.sound.set_volume(volume)  # Set volume dynamically
        self.sound.play()