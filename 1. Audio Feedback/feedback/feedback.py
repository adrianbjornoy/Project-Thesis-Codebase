from abc import ABC, abstractmethod

class FeedbackMechanism(ABC):
    @abstractmethod
    def give_feedback(self,
                      normalized_distance,
                      player_x,
                      player_y,
                      target_x,
                      target_y,
                      max_x,
                      max_y,
                      **kwargs):
        pass