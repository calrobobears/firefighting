/* including this file defines a Kalman filter for a specified process
 *
 * the process is specified by the following inputs
 * INPUTS:
 *            stateN                - the dimensionality of the state
 *            controlN              - the dimensionality of the control input
 *            sensorN               - the dimensionality of the sensor readings
 *            prediction_function   - the function which predicts how the state evolves given the control input
 *            prediction_jacobian   - the function which returns the jacobian of the prediction function
 *            sensor_function       - the function which gives the expected sensor readings for a state
 *            sensor_jacobian       - the function which returns the jacobian of the sensor function
 *            process_name          - name of the process
 * (optional) distribution_typename - the typename of the distribution, default will be distributionN
 */

#define state_space JOIN(real, stateN)
#define state_matrix JOIN(real, JOIN(stateN, JOIN(x, stateN)))
#define state_identity JOIN(identity, stateN)(1)

#define control_space JOIN(real, controlN)

#define sensor_space JOIN(real, sensorN)
#define sensor_matrix JOIN(real, JOIN(sensorN, JOIN(x, sensorN)))

#define state_to_sensor JOIN(real, JOIN(sensorN, JOIN(x, stateN)))
#define sensor_to_state JOIN(real, JOIN(stateN, JOIN(x, sensorN)))

#ifndef distribution_typename
#define distribution_typename JOIN(distribution, stateN)
#endif

#define predict_name JOIN(predict, process_name)
#define update_name JOIN(update, process_name)

struct distribution_typename
{
    state_space state; //the state of the distribution
    state_transform cov; //the covariance of the distribution
};

void predict_name(distribution_typename* dist,
                  control_space control,
                  state_matrix process_noise)
{
    state_matrix F = prediction_jacobian(dist->state, control);
    state_matrix Ft = transpose(F);
    dist->cov = F*dist->state*Ft + process_noise;
    dist->state = prediction_function(dist->state, control)
}

void update_name(distribution_typename* dist,
                 sensor_space sensor_reading,
                 sensor_matrix sensor_noise)
{
    //compare what the sensors actually say to what we think they should say
    sensor_space residual = sensor_reading - sensor_function(dist->space);
    
    state_to_sensor H = sensor_jacobian(dist->state);
    sensor_to_state Ht = transpose(H);
    sensor_matrix residual_cov = H*dist->cov*Ht + sensor_noise;
    sensor_matrix inverse_residual_cov = inverse(residual_cov);
    
    sensor_to_state kalman_gain = dist->cov*Ht*inverse_residual_cov;
    
    dist->state = dist->state + kalman_gain*sensor_reading;
    dist->cov = (state_identity - kalman_gain*H)*dist->cov;
}

//clean up macros
#undef state_space
#undef state_matrix
#undef state_identity
#undef control_space
#undef sensor_space
#undef sensor_matrix
#undef state_to_sensor
#undef sensor_to_state
#undef distribution_typename
#undef predict_name
#undef update_name
