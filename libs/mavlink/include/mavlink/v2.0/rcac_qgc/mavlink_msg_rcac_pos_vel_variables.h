#pragma once
// MESSAGE RCAC_POS_VEL_VARIABLES PACKING

#define MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES 10002


typedef struct __mavlink_rcac_pos_vel_variables_t {
 uint64_t timestamp; /*<  Time since system start*/
 float pid_factor; /*<  PID scaling*/
 float rcac_master_sw; /*<  Master RCAC switch*/
 float alpha_pid_pos; /*<  Gain multiplied by the PID position gains*/
 float alpha_pid_vel; /*<  Gain multiplied by the PID velocity gains*/
 float p11_pos; /*<  P(1,1) of the RCAC Position Controllerr*/
 float p11_velx; /*<  P(1,1) of the RCAC Velocity Controller*/
 float rcac_pos_theta[3]; /*<  P gains for the Position Controller*/
 float rcac_vel_theta[9]; /*<  PID gains for the Velocity Controller*/
 uint8_t switch_pos; /*<  RCAC Position Controller switch*/
 uint8_t switch_vel; /*<  RCAC Velocity Controller switch*/
} mavlink_rcac_pos_vel_variables_t;

#define MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN 82
#define MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_MIN_LEN 82
#define MAVLINK_MSG_ID_10002_LEN 82
#define MAVLINK_MSG_ID_10002_MIN_LEN 82

#define MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_CRC 134
#define MAVLINK_MSG_ID_10002_CRC 134

#define MAVLINK_MSG_RCAC_POS_VEL_VARIABLES_FIELD_RCAC_POS_THETA_LEN 3
#define MAVLINK_MSG_RCAC_POS_VEL_VARIABLES_FIELD_RCAC_VEL_THETA_LEN 9

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_RCAC_POS_VEL_VARIABLES { \
    10002, \
    "RCAC_POS_VEL_VARIABLES", \
    11, \
    {  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_rcac_pos_vel_variables_t, timestamp) }, \
         { "pid_factor", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_rcac_pos_vel_variables_t, pid_factor) }, \
         { "rcac_master_sw", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_rcac_pos_vel_variables_t, rcac_master_sw) }, \
         { "switch_pos", NULL, MAVLINK_TYPE_UINT8_T, 0, 80, offsetof(mavlink_rcac_pos_vel_variables_t, switch_pos) }, \
         { "switch_vel", NULL, MAVLINK_TYPE_UINT8_T, 0, 81, offsetof(mavlink_rcac_pos_vel_variables_t, switch_vel) }, \
         { "alpha_pid_pos", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_rcac_pos_vel_variables_t, alpha_pid_pos) }, \
         { "alpha_pid_vel", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_rcac_pos_vel_variables_t, alpha_pid_vel) }, \
         { "p11_pos", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_rcac_pos_vel_variables_t, p11_pos) }, \
         { "p11_velx", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_rcac_pos_vel_variables_t, p11_velx) }, \
         { "rcac_pos_theta", NULL, MAVLINK_TYPE_FLOAT, 3, 32, offsetof(mavlink_rcac_pos_vel_variables_t, rcac_pos_theta) }, \
         { "rcac_vel_theta", NULL, MAVLINK_TYPE_FLOAT, 9, 44, offsetof(mavlink_rcac_pos_vel_variables_t, rcac_vel_theta) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_RCAC_POS_VEL_VARIABLES { \
    "RCAC_POS_VEL_VARIABLES", \
    11, \
    {  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_rcac_pos_vel_variables_t, timestamp) }, \
         { "pid_factor", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_rcac_pos_vel_variables_t, pid_factor) }, \
         { "rcac_master_sw", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_rcac_pos_vel_variables_t, rcac_master_sw) }, \
         { "switch_pos", NULL, MAVLINK_TYPE_UINT8_T, 0, 80, offsetof(mavlink_rcac_pos_vel_variables_t, switch_pos) }, \
         { "switch_vel", NULL, MAVLINK_TYPE_UINT8_T, 0, 81, offsetof(mavlink_rcac_pos_vel_variables_t, switch_vel) }, \
         { "alpha_pid_pos", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_rcac_pos_vel_variables_t, alpha_pid_pos) }, \
         { "alpha_pid_vel", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_rcac_pos_vel_variables_t, alpha_pid_vel) }, \
         { "p11_pos", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_rcac_pos_vel_variables_t, p11_pos) }, \
         { "p11_velx", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_rcac_pos_vel_variables_t, p11_velx) }, \
         { "rcac_pos_theta", NULL, MAVLINK_TYPE_FLOAT, 3, 32, offsetof(mavlink_rcac_pos_vel_variables_t, rcac_pos_theta) }, \
         { "rcac_vel_theta", NULL, MAVLINK_TYPE_FLOAT, 9, 44, offsetof(mavlink_rcac_pos_vel_variables_t, rcac_vel_theta) }, \
         } \
}
#endif

/**
 * @brief Pack a rcac_pos_vel_variables message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp  Time since system start
 * @param pid_factor  PID scaling
 * @param rcac_master_sw  Master RCAC switch
 * @param switch_pos  RCAC Position Controller switch
 * @param switch_vel  RCAC Velocity Controller switch
 * @param alpha_pid_pos  Gain multiplied by the PID position gains
 * @param alpha_pid_vel  Gain multiplied by the PID velocity gains
 * @param p11_pos  P(1,1) of the RCAC Position Controllerr
 * @param p11_velx  P(1,1) of the RCAC Velocity Controller
 * @param rcac_pos_theta  P gains for the Position Controller
 * @param rcac_vel_theta  PID gains for the Velocity Controller
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rcac_pos_vel_variables_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t timestamp, float pid_factor, float rcac_master_sw, uint8_t switch_pos, uint8_t switch_vel, float alpha_pid_pos, float alpha_pid_vel, float p11_pos, float p11_velx, const float *rcac_pos_theta, const float *rcac_vel_theta)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, pid_factor);
    _mav_put_float(buf, 12, rcac_master_sw);
    _mav_put_float(buf, 16, alpha_pid_pos);
    _mav_put_float(buf, 20, alpha_pid_vel);
    _mav_put_float(buf, 24, p11_pos);
    _mav_put_float(buf, 28, p11_velx);
    _mav_put_uint8_t(buf, 80, switch_pos);
    _mav_put_uint8_t(buf, 81, switch_vel);
    _mav_put_float_array(buf, 32, rcac_pos_theta, 3);
    _mav_put_float_array(buf, 44, rcac_vel_theta, 9);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN);
#else
    mavlink_rcac_pos_vel_variables_t packet;
    packet.timestamp = timestamp;
    packet.pid_factor = pid_factor;
    packet.rcac_master_sw = rcac_master_sw;
    packet.alpha_pid_pos = alpha_pid_pos;
    packet.alpha_pid_vel = alpha_pid_vel;
    packet.p11_pos = p11_pos;
    packet.p11_velx = p11_velx;
    packet.switch_pos = switch_pos;
    packet.switch_vel = switch_vel;
    mav_array_memcpy(packet.rcac_pos_theta, rcac_pos_theta, sizeof(float)*3);
    mav_array_memcpy(packet.rcac_vel_theta, rcac_vel_theta, sizeof(float)*9);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_MIN_LEN, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_CRC);
}

/**
 * @brief Pack a rcac_pos_vel_variables message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp  Time since system start
 * @param pid_factor  PID scaling
 * @param rcac_master_sw  Master RCAC switch
 * @param switch_pos  RCAC Position Controller switch
 * @param switch_vel  RCAC Velocity Controller switch
 * @param alpha_pid_pos  Gain multiplied by the PID position gains
 * @param alpha_pid_vel  Gain multiplied by the PID velocity gains
 * @param p11_pos  P(1,1) of the RCAC Position Controllerr
 * @param p11_velx  P(1,1) of the RCAC Velocity Controller
 * @param rcac_pos_theta  P gains for the Position Controller
 * @param rcac_vel_theta  PID gains for the Velocity Controller
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rcac_pos_vel_variables_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t timestamp,float pid_factor,float rcac_master_sw,uint8_t switch_pos,uint8_t switch_vel,float alpha_pid_pos,float alpha_pid_vel,float p11_pos,float p11_velx,const float *rcac_pos_theta,const float *rcac_vel_theta)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, pid_factor);
    _mav_put_float(buf, 12, rcac_master_sw);
    _mav_put_float(buf, 16, alpha_pid_pos);
    _mav_put_float(buf, 20, alpha_pid_vel);
    _mav_put_float(buf, 24, p11_pos);
    _mav_put_float(buf, 28, p11_velx);
    _mav_put_uint8_t(buf, 80, switch_pos);
    _mav_put_uint8_t(buf, 81, switch_vel);
    _mav_put_float_array(buf, 32, rcac_pos_theta, 3);
    _mav_put_float_array(buf, 44, rcac_vel_theta, 9);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN);
#else
    mavlink_rcac_pos_vel_variables_t packet;
    packet.timestamp = timestamp;
    packet.pid_factor = pid_factor;
    packet.rcac_master_sw = rcac_master_sw;
    packet.alpha_pid_pos = alpha_pid_pos;
    packet.alpha_pid_vel = alpha_pid_vel;
    packet.p11_pos = p11_pos;
    packet.p11_velx = p11_velx;
    packet.switch_pos = switch_pos;
    packet.switch_vel = switch_vel;
    mav_array_memcpy(packet.rcac_pos_theta, rcac_pos_theta, sizeof(float)*3);
    mav_array_memcpy(packet.rcac_vel_theta, rcac_vel_theta, sizeof(float)*9);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_MIN_LEN, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_CRC);
}

/**
 * @brief Encode a rcac_pos_vel_variables struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param rcac_pos_vel_variables C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rcac_pos_vel_variables_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_rcac_pos_vel_variables_t* rcac_pos_vel_variables)
{
    return mavlink_msg_rcac_pos_vel_variables_pack(system_id, component_id, msg, rcac_pos_vel_variables->timestamp, rcac_pos_vel_variables->pid_factor, rcac_pos_vel_variables->rcac_master_sw, rcac_pos_vel_variables->switch_pos, rcac_pos_vel_variables->switch_vel, rcac_pos_vel_variables->alpha_pid_pos, rcac_pos_vel_variables->alpha_pid_vel, rcac_pos_vel_variables->p11_pos, rcac_pos_vel_variables->p11_velx, rcac_pos_vel_variables->rcac_pos_theta, rcac_pos_vel_variables->rcac_vel_theta);
}

/**
 * @brief Encode a rcac_pos_vel_variables struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param rcac_pos_vel_variables C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rcac_pos_vel_variables_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_rcac_pos_vel_variables_t* rcac_pos_vel_variables)
{
    return mavlink_msg_rcac_pos_vel_variables_pack_chan(system_id, component_id, chan, msg, rcac_pos_vel_variables->timestamp, rcac_pos_vel_variables->pid_factor, rcac_pos_vel_variables->rcac_master_sw, rcac_pos_vel_variables->switch_pos, rcac_pos_vel_variables->switch_vel, rcac_pos_vel_variables->alpha_pid_pos, rcac_pos_vel_variables->alpha_pid_vel, rcac_pos_vel_variables->p11_pos, rcac_pos_vel_variables->p11_velx, rcac_pos_vel_variables->rcac_pos_theta, rcac_pos_vel_variables->rcac_vel_theta);
}

/**
 * @brief Send a rcac_pos_vel_variables message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp  Time since system start
 * @param pid_factor  PID scaling
 * @param rcac_master_sw  Master RCAC switch
 * @param switch_pos  RCAC Position Controller switch
 * @param switch_vel  RCAC Velocity Controller switch
 * @param alpha_pid_pos  Gain multiplied by the PID position gains
 * @param alpha_pid_vel  Gain multiplied by the PID velocity gains
 * @param p11_pos  P(1,1) of the RCAC Position Controllerr
 * @param p11_velx  P(1,1) of the RCAC Velocity Controller
 * @param rcac_pos_theta  P gains for the Position Controller
 * @param rcac_vel_theta  PID gains for the Velocity Controller
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_rcac_pos_vel_variables_send(mavlink_channel_t chan, uint64_t timestamp, float pid_factor, float rcac_master_sw, uint8_t switch_pos, uint8_t switch_vel, float alpha_pid_pos, float alpha_pid_vel, float p11_pos, float p11_velx, const float *rcac_pos_theta, const float *rcac_vel_theta)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, pid_factor);
    _mav_put_float(buf, 12, rcac_master_sw);
    _mav_put_float(buf, 16, alpha_pid_pos);
    _mav_put_float(buf, 20, alpha_pid_vel);
    _mav_put_float(buf, 24, p11_pos);
    _mav_put_float(buf, 28, p11_velx);
    _mav_put_uint8_t(buf, 80, switch_pos);
    _mav_put_uint8_t(buf, 81, switch_vel);
    _mav_put_float_array(buf, 32, rcac_pos_theta, 3);
    _mav_put_float_array(buf, 44, rcac_vel_theta, 9);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES, buf, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_MIN_LEN, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_CRC);
#else
    mavlink_rcac_pos_vel_variables_t packet;
    packet.timestamp = timestamp;
    packet.pid_factor = pid_factor;
    packet.rcac_master_sw = rcac_master_sw;
    packet.alpha_pid_pos = alpha_pid_pos;
    packet.alpha_pid_vel = alpha_pid_vel;
    packet.p11_pos = p11_pos;
    packet.p11_velx = p11_velx;
    packet.switch_pos = switch_pos;
    packet.switch_vel = switch_vel;
    mav_array_memcpy(packet.rcac_pos_theta, rcac_pos_theta, sizeof(float)*3);
    mav_array_memcpy(packet.rcac_vel_theta, rcac_vel_theta, sizeof(float)*9);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES, (const char *)&packet, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_MIN_LEN, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_CRC);
#endif
}

/**
 * @brief Send a rcac_pos_vel_variables message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_rcac_pos_vel_variables_send_struct(mavlink_channel_t chan, const mavlink_rcac_pos_vel_variables_t* rcac_pos_vel_variables)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_rcac_pos_vel_variables_send(chan, rcac_pos_vel_variables->timestamp, rcac_pos_vel_variables->pid_factor, rcac_pos_vel_variables->rcac_master_sw, rcac_pos_vel_variables->switch_pos, rcac_pos_vel_variables->switch_vel, rcac_pos_vel_variables->alpha_pid_pos, rcac_pos_vel_variables->alpha_pid_vel, rcac_pos_vel_variables->p11_pos, rcac_pos_vel_variables->p11_velx, rcac_pos_vel_variables->rcac_pos_theta, rcac_pos_vel_variables->rcac_vel_theta);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES, (const char *)rcac_pos_vel_variables, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_MIN_LEN, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_CRC);
#endif
}

#if MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_rcac_pos_vel_variables_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t timestamp, float pid_factor, float rcac_master_sw, uint8_t switch_pos, uint8_t switch_vel, float alpha_pid_pos, float alpha_pid_vel, float p11_pos, float p11_velx, const float *rcac_pos_theta, const float *rcac_vel_theta)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, pid_factor);
    _mav_put_float(buf, 12, rcac_master_sw);
    _mav_put_float(buf, 16, alpha_pid_pos);
    _mav_put_float(buf, 20, alpha_pid_vel);
    _mav_put_float(buf, 24, p11_pos);
    _mav_put_float(buf, 28, p11_velx);
    _mav_put_uint8_t(buf, 80, switch_pos);
    _mav_put_uint8_t(buf, 81, switch_vel);
    _mav_put_float_array(buf, 32, rcac_pos_theta, 3);
    _mav_put_float_array(buf, 44, rcac_vel_theta, 9);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES, buf, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_MIN_LEN, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_CRC);
#else
    mavlink_rcac_pos_vel_variables_t *packet = (mavlink_rcac_pos_vel_variables_t *)msgbuf;
    packet->timestamp = timestamp;
    packet->pid_factor = pid_factor;
    packet->rcac_master_sw = rcac_master_sw;
    packet->alpha_pid_pos = alpha_pid_pos;
    packet->alpha_pid_vel = alpha_pid_vel;
    packet->p11_pos = p11_pos;
    packet->p11_velx = p11_velx;
    packet->switch_pos = switch_pos;
    packet->switch_vel = switch_vel;
    mav_array_memcpy(packet->rcac_pos_theta, rcac_pos_theta, sizeof(float)*3);
    mav_array_memcpy(packet->rcac_vel_theta, rcac_vel_theta, sizeof(float)*9);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES, (const char *)packet, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_MIN_LEN, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_CRC);
#endif
}
#endif

#endif

// MESSAGE RCAC_POS_VEL_VARIABLES UNPACKING


/**
 * @brief Get field timestamp from rcac_pos_vel_variables message
 *
 * @return  Time since system start
 */
static inline uint64_t mavlink_msg_rcac_pos_vel_variables_get_timestamp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field pid_factor from rcac_pos_vel_variables message
 *
 * @return  PID scaling
 */
static inline float mavlink_msg_rcac_pos_vel_variables_get_pid_factor(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field rcac_master_sw from rcac_pos_vel_variables message
 *
 * @return  Master RCAC switch
 */
static inline float mavlink_msg_rcac_pos_vel_variables_get_rcac_master_sw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field switch_pos from rcac_pos_vel_variables message
 *
 * @return  RCAC Position Controller switch
 */
static inline uint8_t mavlink_msg_rcac_pos_vel_variables_get_switch_pos(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  80);
}

/**
 * @brief Get field switch_vel from rcac_pos_vel_variables message
 *
 * @return  RCAC Velocity Controller switch
 */
static inline uint8_t mavlink_msg_rcac_pos_vel_variables_get_switch_vel(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  81);
}

/**
 * @brief Get field alpha_pid_pos from rcac_pos_vel_variables message
 *
 * @return  Gain multiplied by the PID position gains
 */
static inline float mavlink_msg_rcac_pos_vel_variables_get_alpha_pid_pos(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field alpha_pid_vel from rcac_pos_vel_variables message
 *
 * @return  Gain multiplied by the PID velocity gains
 */
static inline float mavlink_msg_rcac_pos_vel_variables_get_alpha_pid_vel(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field p11_pos from rcac_pos_vel_variables message
 *
 * @return  P(1,1) of the RCAC Position Controllerr
 */
static inline float mavlink_msg_rcac_pos_vel_variables_get_p11_pos(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field p11_velx from rcac_pos_vel_variables message
 *
 * @return  P(1,1) of the RCAC Velocity Controller
 */
static inline float mavlink_msg_rcac_pos_vel_variables_get_p11_velx(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field rcac_pos_theta from rcac_pos_vel_variables message
 *
 * @return  P gains for the Position Controller
 */
static inline uint16_t mavlink_msg_rcac_pos_vel_variables_get_rcac_pos_theta(const mavlink_message_t* msg, float *rcac_pos_theta)
{
    return _MAV_RETURN_float_array(msg, rcac_pos_theta, 3,  32);
}

/**
 * @brief Get field rcac_vel_theta from rcac_pos_vel_variables message
 *
 * @return  PID gains for the Velocity Controller
 */
static inline uint16_t mavlink_msg_rcac_pos_vel_variables_get_rcac_vel_theta(const mavlink_message_t* msg, float *rcac_vel_theta)
{
    return _MAV_RETURN_float_array(msg, rcac_vel_theta, 9,  44);
}

/**
 * @brief Decode a rcac_pos_vel_variables message into a struct
 *
 * @param msg The message to decode
 * @param rcac_pos_vel_variables C-struct to decode the message contents into
 */
static inline void mavlink_msg_rcac_pos_vel_variables_decode(const mavlink_message_t* msg, mavlink_rcac_pos_vel_variables_t* rcac_pos_vel_variables)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    rcac_pos_vel_variables->timestamp = mavlink_msg_rcac_pos_vel_variables_get_timestamp(msg);
    rcac_pos_vel_variables->pid_factor = mavlink_msg_rcac_pos_vel_variables_get_pid_factor(msg);
    rcac_pos_vel_variables->rcac_master_sw = mavlink_msg_rcac_pos_vel_variables_get_rcac_master_sw(msg);
    rcac_pos_vel_variables->alpha_pid_pos = mavlink_msg_rcac_pos_vel_variables_get_alpha_pid_pos(msg);
    rcac_pos_vel_variables->alpha_pid_vel = mavlink_msg_rcac_pos_vel_variables_get_alpha_pid_vel(msg);
    rcac_pos_vel_variables->p11_pos = mavlink_msg_rcac_pos_vel_variables_get_p11_pos(msg);
    rcac_pos_vel_variables->p11_velx = mavlink_msg_rcac_pos_vel_variables_get_p11_velx(msg);
    mavlink_msg_rcac_pos_vel_variables_get_rcac_pos_theta(msg, rcac_pos_vel_variables->rcac_pos_theta);
    mavlink_msg_rcac_pos_vel_variables_get_rcac_vel_theta(msg, rcac_pos_vel_variables->rcac_vel_theta);
    rcac_pos_vel_variables->switch_pos = mavlink_msg_rcac_pos_vel_variables_get_switch_pos(msg);
    rcac_pos_vel_variables->switch_vel = mavlink_msg_rcac_pos_vel_variables_get_switch_vel(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN? msg->len : MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN;
        memset(rcac_pos_vel_variables, 0, MAVLINK_MSG_ID_RCAC_POS_VEL_VARIABLES_LEN);
    memcpy(rcac_pos_vel_variables, _MAV_PAYLOAD(msg), len);
#endif
}
