#include "Forces.h"

namespace animation_cw3::forces {
QVector2D gravity(float gravity)
{
    return { 0, -gravity };
}
} // namespace animation_cw3::forces
