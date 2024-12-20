import numpy as np
import matplotlib.pyplot as plt

def force_from_angle(L,a,b,d0,k,alpha):
    F = k*2*a*b*np.tan(alpha)/L * (1-(d0/(np.sqrt(a**2 + b**2 - 2*a*b*np.cos(alpha)))))
    return F

# Parameters
L = 595   # mm
a = 485   # mm
b = 420   # mm
k = 9.81  # N/mm
d0 = 205  # mm
z0 = 252  # mm (initial vertical position)
z1 = z0 - 50  # mm (vertical position after compression)


# Convert vertical positions to angles
alpha_0 = np.arcsin(z0/L)
alpha_1 = np.arcsin(z1/L)

print("Start Angle (deg):", alpha_0 * 180/np.pi)
print("Stop Angle (deg):", alpha_1 * 180/np.pi)

alpha_range = np.linspace(alpha_0,alpha_1,100)

F = force_from_angle(L,a,b,d0,k,alpha_range)


# Calculate displacement: difference from the initial vertical position
z = L * np.sin(alpha_range)
displacement = z0 - z  # how far has the system compressed from z0
# Plot force vs. displacement for the original range
plt.figure(figsize=(8, 6))
plt.plot(displacement, F, label='Compression distance ~50 mm')
plt.title("Force vs. Displacement")
plt.xlabel("Displacement (mm)")
plt.ylabel("Force (N)")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

z2 = z0 - 150
alpha_2 = np.arcsin(z2/L)
alpha_range_large = np.linspace(alpha_0, alpha_2, 100)
F_large = force_from_angle(L, a, b, d0, k, alpha_range_large)
z_large = L * np.sin(alpha_range_large)
displacement_large = z0 - z_large

# Plot force vs. displacement for the larger compression
plt.figure(figsize=(8, 6))
plt.plot(displacement_large, F_large, label='Compression distance ~150 mm', color='r')
plt.title("Force vs. Displacement (Larger Compression)")
plt.xlabel("Displacement (mm)")
plt.ylabel("Force (N)")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
