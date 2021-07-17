import numpy as np
from . import algo1_ext

# A wrapper function to call the C++ extension
# It enables proper docstring
def cpp_multiply(data: np.ndarray, k: float) -> np.ndarray:
    """Multiple all elements by k

    Args:
        data (np.ndarray): 1d np.array of dtype=np.double
        k (float): k

    Returns:
        np.ndarray: 1d np.array
    """
    result = np.empty(data.size)
    algo1_ext.multiply_by(data, result, k)
    return result