import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Load the data
df = pd.read_csv("C:\\Users\\adria\\OneDrive\\Skrivebord\\total_statistics.csv")

# Quick look at the data
print(df.head())
print(df.info())
print(df.describe())

# Create a dictionary of old names to new names
feedback_method_mapping = {
    'beep_rate': 'Beep Rate / Frequency',
    'directional': 'Directional',
    'volume': 'Volume / Intensity',
    'pitch': 'Pitch / Brightness',
    'relative': 'Relative'
}

# Replace the values in the dataframe
df['feedback_method'] = df['feedback_method'].replace(feedback_method_mapping)

# Group data and get mean and standard error (not strictly needed for plotting, but kept for reference)
grouped = df.groupby(['mode', 'feedback_method']).agg({'time': ['mean', 'sem'], 'clicks': ['mean', 'sem']}).reset_index()
grouped.columns = ['mode', 'feedback_method', 'time_mean', 'time_sem', 'clicks_mean', 'clicks_sem']

# Get the unique levels
levels = df['level'].unique()

# Box plot for time
plt.figure(figsize=(10, 6))
sns.boxplot(data=df, x='feedback_method', y='time', hue='mode')
plt.title("Distribution of Completion Times by Feedback Method and Mode")
plt.xlabel("Feedback Method")
plt.ylabel("Elapsed Time")
plt.xticks(rotation=45)
plt.tight_layout()
#plt.ylim(0, 70)
plt.show()

# Box plot for clicks
plt.figure(figsize=(10, 6))
sns.boxplot(data=df, x='feedback_method', y='clicks', hue='mode')
plt.title("Distribution of Clicks by Feedback Method and Mode")
plt.xlabel("Feedback Method")
plt.ylabel("Number of Attempts / Clicks")
plt.xticks(rotation=45)
plt.tight_layout()
#plt.ylim(0, 50)
plt.show()

# Plot time boxplots for each level
for lvl in levels:
    df_level = df[df['level'] == lvl]
    plt.figure(figsize=(10, 6))
    sns.boxplot(data=df_level, x='feedback_method', y='time', hue='mode')
    plt.title(f"Distribution of Completion Times by Feedback Method and Mode - Level {lvl}")
    plt.xlabel("Feedback Method")
    plt.ylabel("Elapsed Time")
    plt.xticks(rotation=45)
    plt.ylim(0, 100)  # Set the same Y-axis limit for all plots
    plt.tight_layout()
    plt.show()

# Plot clicks boxplots for each level
for lvl in levels:
    df_level = df[df['level'] == lvl]
    plt.figure(figsize=(10, 6))
    sns.boxplot(data=df_level, x='feedback_method', y='clicks', hue='mode')
    plt.title(f"Distribution of Clicks by Feedback Method and Mode - Level {lvl}")
    plt.xlabel("Feedback Method")
    plt.ylabel("Number of Attempts / Clicks")
    plt.xticks(rotation=45)
    plt.ylim(0, 100)  # Same Y-axis limit for all plots for consistency
    plt.tight_layout()
    plt.show()