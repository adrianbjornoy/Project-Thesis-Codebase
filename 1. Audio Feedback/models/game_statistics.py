import csv
import os
from datetime import datetime

from config import Config

class GameStatistics:
    def __init__(self):
        self.level_stats = []

    def add_level_stat(self, level, time, clicks, feedback_method):
        self.level_stats.append({
            'level': level,
            'time': time,
            'clicks': clicks,
            'feedback_method': feedback_method,
            'timestamp': datetime.now().isoformat()
        })

    def write_to_csv(self, filename=Config.OUTPUT_STATISTICS.string):
        file_exists = os.path.isfile(filename)
        
        with open(filename, 'a', newline='') as csvfile:
            fieldnames = ['level', 'time', 'clicks', 'feedback_method', 'timestamp']
            writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
            if not file_exists:
                writer.writeheader()
            for stat in self.level_stats:
                writer.writerow(stat)

    def reset(self):
        self.level_stats = []

