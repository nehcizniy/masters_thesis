import numpy as np
import matplotlib.pyplot as plt

# Parameters
lambda_param = 0.2  # Adjust as needed
xmin, xmax = 1, 11
num_samples = 10000

# Generate random numbers following exponential distribution
data = np.random.exponential(scale=1/lambda_param, size=num_samples)

# Create histograms
hist_10bins, edges_10bins = np.histogram(data, bins=10, range=(xmin, xmax))
hist_100bins, edges_100bins = np.histogram(data, bins=100, range=(xmin, xmax))

# Plot histograms
plt.figure(figsize=(12, 6))

plt.subplot(1, 2, 1)
plt.hist(data, bins=10, range=(xmin, xmax), alpha=0.7, color='b', label='Histogram (10 bins)')
plt.title('Histogram with 10 bins')
plt.xlabel('x')
plt.ylabel('Frequency')
plt.legend()

plt.subplot(1, 2, 2)
plt.hist(data, bins=100, range=(xmin, xmax), alpha=0.7, color='r', label='Histogram (100 bins)')
plt.title('Histogram with 100 bins')
plt.xlabel('x')
plt.ylabel('Frequency')
plt.legend()

plt.tight_layout()
plt.show()

# Calculate x mean for each histogram
x_mean_10bins = np.mean(edges_10bins[:-1] + np.diff(edges_10bins)/2)
x_mean_100bins = np.mean(edges_100bins[:-1] + np.diff(edges_100bins)/2)

# Calculate the difference between x means
x_mean_difference = x_mean_100bins - x_mean_10bins

print(f"X mean for 10 bins: {x_mean_10bins}")
print(f"X mean for 100 bins: {x_mean_100bins}")
print(x_mean_difference)
