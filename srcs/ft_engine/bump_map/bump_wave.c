#include <ft_bump_map.h>
#include <ft_floats.h>
#include <libft.h>
#include <main.h>


t_bump	*bump_wave(void)
{
	t_bump	*bump;

	bump = bump_new_bump();
	bump->type = BUMP_WAVE;
	return (bump);
}

t_vec bump_wave_normal_at(t_bump bump, t_point point, t_vec base_normal)
{
    // Wave parameters
    const int NUM_WAVES = 5; // Number of wave components
    //double amplitudes[NUM_WAVES]  = {1.0, 0.5, 0.3, 0.2, 0.1};
    double amplitudes[NUM_WAVES]  = {0.01, 0.05, 0.03, 0.02, 0.01};
    double wavelengths[NUM_WAVES] = {30.0, 15.0, 10.0, 5.0, 2.5};
    double speeds[NUM_WAVES]      = {1.0, 1.5, 2.0, 2.5, 3.0};
    double directions[NUM_WAVES][2] = {
        {1.0, 0.0},
        {0.7, 0.7},
        {0.0, 1.0},
        {-0.7, 0.7},
        {-1.0, 0.0}
    };
    double phases[NUM_WAVES] = {0.0, 1.0, 2.0, 3.0, 4.0};
    double time = 0.0; // Set time to zero for static waves

    // Initialize partial derivatives
    double d_dx = 0.0;
    double d_dy = 0.0;
    double d_dz = 0.0;

    double x = point.x;
    double z = point.z;

    for (int i = 0; i < NUM_WAVES; i++)
    {
        double amplitude = amplitudes[i];
        double wavelength = wavelengths[i];
        double speed = speeds[i];
        double phase = phases[i];
        double k = 2.0 * M_PI / wavelength; // Wave number
        double omega = k * speed;           // Angular frequency
        double dir_x = directions[i][0];
        double dir_z = directions[i][1];

        // Normalize direction vector
        double dir_length = sqrt(dir_x * dir_x + dir_z * dir_z);
        dir_x /= dir_length;
        dir_z /= dir_length;

        double dot = k * (dir_x * x + dir_z * z) - omega * time + phase;
        double cos_dot = cos(dot);
        double sin_dot = sin(dot);

        // Accumulate partial derivatives
        d_dx += amplitude * k * dir_x * cos_dot;
        d_dy += amplitude * k * sin_dot;
        d_dz += amplitude * k * dir_z * cos_dot;
    }

    // Compute the perturbed normal
    t_vec perturbed_normal;
    perturbed_normal.x = -d_dx;
    perturbed_normal.y = base_normal.y - d_dy; // base_normal.y should be 1.0 for a flat plane
    perturbed_normal.z = -d_dz;
    perturbed_normal.w = 0.0; // Since it's a vector

    // Normalize the perturbed normal
    //perturbed_normal = norm(perturbed_normal);
	//perturbed_normal = mtx_mult_mt(mtx_rotation_x(-M_PI_4 * 2), perturbed_normal);
	//perturbed_normal = mult_v(perturbed_normal, -1.0);
	perturbed_normal = norm(perturbed_normal);
	//print_t(2, perturbed_normal);
    return (perturbed_normal);
}

