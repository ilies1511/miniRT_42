// #include <ft_bump_map.h>
// #include <ft_floats.h>
// #include <libft.h>
// #include <main.h>


// t_bump	*bump_wave(void)
// {
// 	t_bump	*bump;

// 	bump = bump_new_bump();
// 	bump->type = BUMP_WAVE;
// 	return (bump);
// }

// //t_vec bump_wave_normal_at(t_bump bump, t_point point, t_vec base_normal)
// //{
// //    t_vec z_axis;
// //    t_vec rotation_axis;
// //    t_matrix rotation_matrix;
// //    double angle;
// //
// //    // Initialize z_axis as (0, 0, 1)
// //    z_axis = new_vec(0, 0, 1);
// //
// //    // Check if base_normal is equal to z_axis
// //    if (eq_t(base_normal, z_axis))
// //	{
// //        // TODO: Handle the special case where the base normal is aligned with z-axis
// //        return base_normal;
// //    }
// //
// //    // Compute the rotation axis as the cross product of base_normal and z_axis
// //    rotation_axis = cross_prod(base_normal, z_axis);
// //
// //    // Compute the angle of rotation based on the sine of point.z
// //    double interval = 10.0;  // Spatial period of the waves
// //    double amplitude = 0.5 * M_PI;  // Max rotation of 0.25 PI radians
// //    angle = amplitude * sin((2 * M_PI / interval) * point.z);
// //
// //    // Create a rotation matrix to rotate around the rotation axis by the computed angle
// //    rotation_matrix = mtx_rotation_axis_angle(rotation_axis, angle);
// //
// //    // Return the rotated base normal
// //    return mtx_mult_mt(rotation_matrix, base_normal);
// //
// //    (void)bump;  // Avoid unused parameter warning
// //}

// // Function to compute the wave normal at an intersection point

// t_vec compute_wave_normal_pre(t_point intersection_point, t_vec normal) {
//     double x = intersection_point.x;
//     double z = intersection_point.z;

//     // Wave parameters for multiple waves
//     double amplitudes[] = {1.0, 0.5};
//     double frequencies[] = {1.0, 2.0};
//     double phases[] = {0.0, M_PI / 4};

//     double dW_dx = 0.0;
//     double dW_dz = 0.0;

//     // Sum the gradients of multiple wave functions
//     for (int i = 0; i < 2; i++) {
//         double amplitude = amplitudes[i];
//         double frequency = frequencies[i];
//         double phase = phases[i];

//         dW_dx += amplitude * frequency * cos(frequency * x + phase) * sin(frequency * z + phase);
//         dW_dz += amplitude * frequency * sin(frequency * x + phase) * cos(frequency * z + phase);
//     }

//     // Compute the perturbed normal
//     normal.x = -dW_dx;
//     normal.y = 1.0;
//     normal.z = -dW_dz;

//     // Normalize the normal vector
//    return( norm(normal));
// }

// t_vec compute_wave_normal(t_point point, t_vec base_normal) {
//     double x = point.x;
//     double z = point.z;

//     // Wave parameters: amplitudes, frequencies, phases
//     double amplitudes[] = {1.0, 0.5};  // Control wave heights
//     double frequencies[] = {1.0, 2.0}; // Control wave density
//     double phases[] = {0.0, M_PI / 4}; // Phase shifts

//     double dW_dx = 0.0;
//     double dW_dz = 0.0;

//     // Sum the gradients of multiple wave functions
//     for (int i = 0; i < 2; i++) {
//         double amplitude = amplitudes[i];
//         double frequency = frequencies[i];
//         double phase = phases[i];

//         // Compute partial derivatives of wave functions
//         dW_dx += amplitude * frequency * cos(frequency * x + phase) * sin(frequency * z + phase);
//         dW_dz += amplitude * frequency * sin(frequency * x + phase) * cos(frequency * z + phase);
//     }

//     // Perturb the base normal with the computed wave effects
//     base_normal.x -= dW_dx;
//     base_normal.z -= dW_dz;

//     // Normalize the perturbed normal
//     return norm(base_normal);
// }


// // Function to create a realistic ocean wave normal
// t_vec bump_wave_normal_at(t_bump bump, t_point point, t_vec base_normal) {
// 	return (compute_wave_normal(point, base_normal));
//     t_vec z_axis;
//     t_vec rotation_axis;
//     t_matrix rotation_matrix;
//     double angle_x, angle_z;

//     // Initialize z_axis as (0, 0, 1)
//     z_axis = new_vec(0, 0, 1);

//     // Check if base_normal is equal to z_axis
//     if (eq_t(base_normal, z_axis)) {
//         // TODO: Handle the special case where the base normal is aligned with z-axis
//         return base_normal;
//     }

//     // Compute the rotation axis as the cross product of base_normal and z_axis
//     rotation_axis = cross_prod(base_normal, z_axis);

//     // Compute the angle of rotation based on the sum of sine waves in both x and z directions
//     double interval_x = 15.0;  // Spatial period of the waves along x-axis
//     double interval_z = 20.0;  // Spatial period of the waves along z-axis
//     double amplitude = 0.1 * M_PI;  // Max rotation of 0.1 PI radians

//     // Compute angles for rotation based on sine waves for both x and z directions
//     angle_x = amplitude * sin((2 * M_PI / interval_x) * point.x);
//     angle_z = amplitude * sin((2 * M_PI / interval_z) * point.z);

//     // Combine the angles for more realistic wave behavior
//     double combined_angle = angle_x + angle_z;

//     // Create a rotation matrix to rotate around the rotation axis by the computed combined angle
//     rotation_matrix = mtx_rotation_axis_angle(rotation_axis, combined_angle);

//     // Return the rotated base normal
//     return mtx_mult_mt(rotation_matrix, base_normal);
// }



// t_vec	bump_wave_normal_at1(t_bump bump, t_point point, t_vec base_normal)
// {
// 	t_vec		z_axis;
// 	t_vec		rotation_axis;
// 	t_matrix	rotation_matrix;
// 	double		angle;

// 	z_axis = new_vec(0, 0, 1);
// 	if (eq_t(base_normal, z_axis))
// 	{
// 		//TODO: what to do here
// 		return (base_normal);
// 	}
// 	rotation_axis = cross_prod(base_normal, z_axis);
// 	// angle = sin(point.z);

// 	/*
// 	2pi - 1.75 pi
// 	1.75pi - 2pi
// 	0pi-0.25pi
// 	0.25pi-0pi
// 	*/
// 	double intervall = 10.0;
// 	double rem = fmod(point.z, intervall);
// 	angle = (((rem / intervall) * M_PI * 2) / 4) - (0.25 * M_PI);
// 	rotation_matrix = mtx_rotation_axis_angle(rotation_axis, angle);
// 	rotation_matrix = mtx_rotation_x(angle);

// 	double interval = 10.0;  // The spatial period of the waves
// 	double amplitude = 0.25 * M_PI;  // Max rotation of 0.25 PI radians
// 	angle = amplitude * sin((2 * M_PI / interval) * point.z);
// 	return (mtx_mult_mt(rotation_matrix, base_normal));
// 	(void)bump;
// }

// // Function to compute wave influence based on position
// double waveFunction(double position)
// {
//     return sin(position);
// }

// // Function to compute the perturbed normal at a point on the ocean surface
// t_vec bump_wave_normal_at2(t_bump bump, t_vec normal, t_vec point) {
//     // Adjust the strength of the wave effect
//     double amplitude = 0.4;  // This controls the height of the waves

//     // Compute wave effects based on the x or z position
//     double waveX = amplitude * waveFunction(point.x);
//     double waveZ = amplitude * waveFunction(point.z);

//     // Create a new vector from the original normal, perturbed by the wave functions
//     t_vec newNormal = { normal.x + waveX, normal.y, normal.z + waveZ , .w=0};

//     // Normalize the result to ensure it's a valid normal
//     return norm(newNormal);
// }
