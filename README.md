OVERVIEW

    This project implements a 2D sensor fusion and state estimation system for a simulated vehicle. The system uses a Kalman Filter to estimate position and velocity in real time by combining a simplified motion model with noisy sensor measurements.

    The simulation is structured to reflect real-world navigation systems by seperating: 
        > Truth Model (true dynamics)
        > Sensor Models (noisy measurements)
        > State Estimator (Kalman Filter)

    The Estimator assumes a constant-velocity motion model, while the truth model includes additional dynamics (acceleration), creating a realistic mismatch that the filter must correct using measurement updates and uncertainty modeling. 

PROBLEM STATMENT

    In real-world navigation systems, the true state of a vehicle (position and velocity) cannot be measured directly. Instead, it must be estimated using imperfect sensor data and simplified models of system dynamics. 

    Sensor measurements are inherently noisy and may provide only parial information about the system, while motion models are often approximations that do not fully capture real dynamics. Relying solely on either source leads to inaccurate or unstable estimates. 

    The problem demonstrated and addressed in this project is to demonstrate a method for combining noisy sensor measurements with a simplified motion model to produce an accurate and stable estimate of the system state in real time. This includes handling model uncertainty, and understanding how estimation performance depends on the balance between model prediction and measurement correction.

SYSTEM ARCHITECTURE

    The system is primarily comprised of four compenents:
    
    Truth Model

        The Truth Model represents the simulated "real" motion of the vehicle. It represents the ground-truth state over time, including position and velocity, in addition to acceleration to create a realistic mismatch with the estimator model. 

        This component shall serve as the reference trajectory from which sensor measurements are generated. 

    Sensor Models

        The Sensor Models generat noisy measurements from the truth state. These measurements represent what an onboard navigatino system would actually observe, rather than the exact state. 

        For the initial implementation, the project uses a GPS-like sensor that provides noisy 2D position measurements. Additional sensors such as an IMU can be added in future extensions.

    State Estimator 

        The state estimator uses a linear Kalman Filter to estimate the system state from noisy measurements. The estimator assumes a simplified constant-velocity model and produces estimates of position and velocity over time.

        By combining motion-model predictions with sensor updates, the estimator reduces measurement noise and compensates for model mismatch.

    Analysis and Visualization

        The analysis layer compares the estimated state against both the noisy measurements and the truth trajectory. This component is used to evaluate estimator performance through trajectory plots, error plots, and summary metrics such as RMSE.

    These are the four cour pillars of this project. 

    At each simulation timestep, the system operates in the following order:

    The truth model propagates the real system state
    The sensor model generates noisy measurements from that truth state
    The Kalman filter predicts and updates the estimated state
    The results are logged for post-processing and visualization

    This separation between truth generation, measurement simulation, and estimation reflects the structure of real-world navigation systems.

STATE REPRESENTATION

    The system state is defined as a 2D vector containing position and velocity components:

    x = [x, y, vx, vy]

    where:
        > x and y represent position in the horizontal plane
        > vx and vy represent velocity in each direction

    This representation provides a minimal state sufficient to describe the motion of the system while enabling prediction of future states using a constant-velocity model.

    Although the simulated truth model may include additional dynamics such as acceleration, these effects are not explicitly modeled in the estimator. Instead, they are treated as unmodeled dynamics and accounted for through process noise within the Kalman Filter.

DYNAMICS MODEL

    The truth model represents the simulated "real" motion of the system and is used to generate the ground-truth state over time.

    The system is modeled as a 2D point mass with position and velocity states. Unlike the estimator, the truth model includes additional dynamics in the form of time-varying acceleration. This allows the simulated motion to deviate from the constant-velocity assumption used in the estimator.

    At each timestep, the system state is propagated forward using basic kinematic relationships, where position is updated based on velocity, and velocity is updated based on applied acceleration.

    The inclusion of acceleration in the truth model introduces a mismatch between the true system dynamics and the estimator model. This mismatch is intentional and reflects real-world scenarios where system dynamics are not perfectly known. The Kalman Filter must account for this discrepancy through measurement updates and process noise.

SENSOR MODELS

STATE ESTIMATION

PROCESS AND MEASUREMENT NOICE

SIMULATION WORKFLOW

RESULTS AND VISUALIZATION

PERFORMANCE METRICS

HOW TO RUN

PROJECT STRUCTURE