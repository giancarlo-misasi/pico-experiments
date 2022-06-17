#include <math/algorithms.hpp>

namespace math
{
    int scale_range(int value, float old_min, float old_max, float new_min, float new_max)
    {
        float adjusted_value = (float) value - old_min;
        float scale = (new_max - new_min) / (old_max - old_min);
        float result = new_min + scale * adjusted_value;
        if (result < new_min)
        {
            result = new_min;
        }
        else if (result > new_max)
        {
            result = new_max;
        }
        return (int) result;
    }
}
