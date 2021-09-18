clc, clear all, close all
%%
a   = arduino();
%%
fs      = 100; % sample rate in Hz.
imu     = mpu6050(a,'SampleRate',fs,'OutputFormat','matrix');
%%
[accel, gyro] = imu.read;
data_read = [accel gyro];
data_matrix = data_read{:,:};
data_mean = mean(data_matrix);


% accel
accel_x_g = accel(:,1)/9.81;
accel_y_g = accel(:,2)/9.81;
accel_z_g = accel(:,3)/9.81;
% gyro
gyro_x_rad = gyro(:,1)
gyro_y_rad = gyro(:,2)
gyro_z_rad = gyro(:,3)

gyro_x_deg = gyro(:,1)*(180/pi);
gyro_y_deg = gyro(:,2)*(180/pi);
gyro_z_deg = gyro(:,3)*(180/pi);



%%

accel_count = 0;
accel_data = [];

while accel_count < 200
    accel_count = accel_count+1;
    
    %
    [accel, gyro] = imu.read;
    data_read = [accel gyro];
    data_matrix = data_read{:,:};
    data_mean = mean(data_matrix);
    
    
    accel_x_ms = data_mean(:,1);
    accel_y_ms = data_mean(:,2);
    accel_z_ms = data_mean(:,3);
    
    
    % capturing data silently
    accel_data = [accel_data; [accel_x_ms, accel_y_ms,accel_z_ms]];
    
    % command window
    
    show_me_data = [accel_x_ms,accel_y_ms,accel_z_ms]
    
    if accel_count == 200
        disp('This is the end of the accelometer session')
    end
end

accel_data;
accel_table = array2table(accel_data,'VariableNames', {'Time (s)', 'Acc-x','Acc-y','Acc-z'});