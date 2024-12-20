from pathlib import Path


class File:
    def __init__(self, path: Path):
        self.path = path

    @property
    def string(self) -> str:
        return str(self.path.resolve())


class Config:
    # Paths
    PATH_TOP_LEVEL = Path(__file__).parent.parent
    PATH_CPR_APP = PATH_TOP_LEVEL / "audio_feedback_v1"
    PATH_SOUNDS = PATH_CPR_APP / "sounds"
    PATH_RESULTS_FILE = PATH_CPR_APP / "results.csv"
    PATH_KV_FILES = PATH_CPR_APP / "kv"

    OUTPUT_STATISTICS = File(PATH_CPR_APP / "game_statistics.csv")

    # Sounds
    BEEP_SOUND_PATH = PATH_SOUNDS / "standard_beep.wav"
    CORRECT_SOUND_PATH = PATH_SOUNDS / "correct_answer.wav"

    LEFT_SOUND_PATH = PATH_SOUNDS / "left.wav"
    RIGHT_SOUND_PATH = PATH_SOUNDS / "right.wav"
    UP_SOUND_PATH = PATH_SOUNDS / "up.wav"
    DOWN_SOUND_PATH = PATH_SOUNDS / "down.wav"

    POSITIVE_SOUND_PATH = PATH_SOUNDS / "correct_direction.mp3"
    NEGATIVE_SOUND_PATH = PATH_SOUNDS / "wrong_direction.mp3"

    # Pitch feedback configuration
    BASE_FREQUENCY = 500
    MAX_FREQUENCY = 2000
    # Beep rate feedback configuration
    MIN_BEEP_INTERVAL = 0.1  # Minimum interval between beeps (seconds)
    MAX_BEEP_INTERVAL = 1.3  # Maximum interval between beeps (seconds)

    # Number of rows and columns indexed by levels
    GRID_SIZES = {1: [6,6],
                  2: [12,12],
                  3: [24,24],
                  4: [32,32]}

    # GRID_SIZES = {1: [6,6],
    #             2: [12,12]}
