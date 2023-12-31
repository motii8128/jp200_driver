#ifndef UTILS_HPP_
#define UTILS_HPP_

#define READ_EMPTY "emp"
#define READ_ERROR "err"

#include <vector>
#include <string>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <linux/serial.h>
#include <string>
#include <vector>

namespace jp200_driver
{
    class JP200Utils{
        public:
            struct Gains
            {
                bool enable;
                float p;
                float i;
                float d;
                float f;
            };

            struct Cmd
            {
                bool enable;
                float value;
                int trajectory;
                float transition_time;
                bool get_state;
            };

            struct JP200Cmd
            {
                int id;
                bool enable_control_mode;
                uint8_t control_mode;
                Cmd angle;
                Cmd velocity;
                Cmd current;
                bool pwm_enable;
                double pwm_rate;
                bool get_pwm;
                bool get_mpu_temp;
                bool get_amp_temp;
                bool get_motor_temp;
                bool get_voltage;
                bool get_status;
                Gains position_gain;
                Gains velocity_gain;
                Gains current_gain; 

                bool error_checker;
            };

            struct Response
            {
                int id;
                bool control_mode;
                bool target_angle;
                bool target_velocity;
                bool target_current;
                bool target_pwm;
                bool target_position_gain;
                bool target_velocity_gain;
                bool target_current_gain;
                float angle_feedback;
                float velocity_feedback;
                float current_feedback;
                float pwm_feedback;
                float mpu_temp_feedback;
                float amp_temp_feedback;
                float motor_temp_feedback;
                float voltage_feedback;
                float status_feedback;
            };
            
            std::string createJp200Cmd(std::vector<JP200Cmd> cmd, bool enable_response);
            Response getResponse(std::string rx_packet, int motor_id);
            int open_port(std::string port_name, int baud_rate);
            void close_port(int fd);
            std::string read_serial(int fd);
            int write_serial(int fd, std::string tx_packet);
            speed_t get_baud_rate(int baud_rate);

    };
}

#endif