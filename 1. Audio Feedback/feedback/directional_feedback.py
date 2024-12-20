import pygame

from feedback.feedback import FeedbackMechanism
from config import Config

class DirectionalFeedback(FeedbackMechanism):
    def __init__(self):
        # Load the sound files for each direction
        self.sound_files = {
            'left': pygame.mixer.Sound(str(Config.LEFT_SOUND_PATH)),
            'right': pygame.mixer.Sound(str(Config.RIGHT_SOUND_PATH)),
            'up': pygame.mixer.Sound(str(Config.UP_SOUND_PATH)),
            'down': pygame.mixer.Sound(str(Config.DOWN_SOUND_PATH))
        }

    def give_feedback(self,
                      normalized_distance,
                      player_x,
                      player_y,
                      target_x,
                      target_y,
                      max_x,
                      max_y):
        # Determine the deltas
        dx = target_x - player_x
        dy = target_y - player_y
        print(dx,dy)
        direction = None
        if dx == 0 and dy == 0:
            # Correct position; no feedback needed
            return

        # Check horizontal movement possibilities
        if dx > 0 and abs(dx) >= abs(dy):
            direction = 'right'
        elif dx < 0 and abs(dx) >= abs(dy):
            direction = 'left'
        elif dy > 0:
            direction = 'down'
        else:
            direction = 'up'

        self.sound_files[direction].play()