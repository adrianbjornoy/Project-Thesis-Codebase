from kivy.uix.button import Button
from kivy.uix.gridlayout import GridLayout
from kivymd.app import MDApp

class ClickableGrid(GridLayout):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.create_grid()
        self.size_hint = (1, 1)


    def create_grid(self):
        # Clear existing widgets
        self.clear_widgets()
        # Get the app instance
        app = MDApp.get_running_app()
        # Update the number of columns and rows based on the current level
        self.cols = app.current_columns
        self.rows = app.current_rows

        # Create the grid buttons
        for y in range(self.rows):
            for x in range(self.cols):
                button = Button(
                    text="",
                    on_press=lambda btn, x=x, y=y: self.on_click(x, y)
                )
                self.add_widget(button)


    def on_click(self, x, y):
        # Update the clicked position (x, y) on the grid
        app = MDApp.get_running_app()
        app.update_position(x, y)

