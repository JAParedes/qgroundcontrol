#pragma once
// MESSAGE RCAC_ATT_RATE_VARIABLES PACKING

#define MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES 10001


typedef struct __mavlink_rcac_att_rate_variables_t {
 uint64_t timestamp; /*<  Time since system start*/
 float alpha_pid_att; /*<  Gain multiplied by the PID attitude gains*/
 float alpha_pid_rate; /*<  Gain multiplied by the PID rate gains*/
 float p11_att; /*<  P(1,1) of the RCAC Attitude Controller*/
 float p11_ratex; /*<  P(1,1) of the RCAC Rate Controller*/
 float rcac_att_theta[3]; /*<  P gains for the Attitude Controller*/
 float rcac_rate_theta[12]; /*<  PID+FF gains for the Rate Controller*/
 uint8_t switch_att; /*<  RCAC Att Controller switch*/
 uint8_t switch_rate; /*<  RCAC Rate Controller switch*/
} mavlink_rcac_att_rate_variables_t;

#define MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN 86
#define MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_MIN_LEN 86
#define MAVLINK_MSG_ID_10001_LEN 86
#define MAVLINK_MSG_ID_10001_MIN_LEN 86

#define MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_CRC 84
#define MAVLINK_MSG_ID_10001_CRC 84

#define MAVLINK_MSG_RCAC_ATT_RATE_VARIABLES_FIELD_RCAC_ATT_THETA_LEN 3
#define MAVLINK_MSG_RCAC_ATT_RATE_VARIABLES_FIELD_RCAC_RATE_THETA_LEN 12

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_RCAC_ATT_RATE_VARIABLES { \
    10001, \
    "RCAC_ATT_RATE_VARIABLES", \
    9, \
    {  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_rcac_att_rate_variables_t, timestamp) }, \
         { "switch_att", NULL, MAVLINK_TYPE_UINT8_T, 0, 84, offsetof(mavlink_rcac_att_rate_variables_t, switch_att) }, \
         { "switch_rate", NULL, MAVLINK_TYPE_UINT8_T, 0, 85, offsetof(mavlink_rcac_att_rate_variables_t, switch_rate) }, \
         { "alpha_pid_att", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_rcac_att_rate_variables_t, alpha_pid_att) }, \
         { "alpha_pid_rate", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_rcac_att_rate_variables_t, alpha_pid_rate) }, \
         { "p11_att", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_rcac_att_rate_variables_t, p11_att) }, \
         { "p11_ratex", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_rcac_att_rate_variables_t, p11_ratex) }, \
         { "rcac_att_theta", NULL, MAVLINK_TYPE_FLOAT, 3, 24, offsetof(mavlink_rcac_att_rate_variables_t, rcac_att_theta) }, \
         { "rcac_rate_theta", NULL, MAVLINK_TYPE_FLOAT, 12, 36, offsetof(mavlink_rcac_att_rate_variables_t, rcac_rate_theta) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_RCAC_ATT_RATE_VARIABLES { \
    "RCAC_ATT_RATE_VARIABLES", \
    9, \
    {  { "timestamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_rcac_att_rate_variables_t, timestamp) }, \
         { "switch_att", NULL, MAVLINK_TYPE_UINT8_T, 0, 84, offsetof(mavlink_rcac_att_rate_variables_t, switch_att) }, \
         { "switch_rate", NULL, MAVLINK_TYPE_UINT8_T, 0, 85, offsetof(mavlink_rcac_att_rate_variables_t, switch_rate) }, \
         { "alpha_pid_att", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_rcac_att_rate_variables_t, alpha_pid_att) }, \
         { "alpha_pid_rate", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_rcac_att_rate_variables_t, alpha_pid_rate) }, \
         { "p11_att", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_rcac_att_rate_variables_t, p11_att) }, \
         { "p11_ratex", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_rcac_att_rate_variables_t, p11_ratex) }, \
         { "rcac_att_theta", NULL, MAVLINK_TYPE_FLOAT, 3, 24, offsetof(mavlink_rcac_att_rate_variables_t, rcac_att_theta) }, \
         { "rcac_rate_theta", NULL, MAVLINK_TYPE_FLOAT, 12, 36, offsetof(mavlink_rcac_att_rate_variables_t, rcac_rate_theta) }, \
         } \
}
#endif

/**
 * @brief Pack a rcac_att_rate_variables message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param timestamp  Time since system start
 * @param switch_att  RCAC Att Controller switch
 * @param switch_rate  RCAC Rate Controller switch
 * @param alpha_pid_att  Gain multiplied by the PID attitude gains
 * @param alpha_pid_rate  Gain multiplied by the PID rate gains
 * @param p11_att  P(1,1) of the RCAC Attitude Controller
 * @param p11_ratex  P(1,1) of the RCAC Rate Controller
 * @param rcac_att_theta  P gains for the Attitude Controller
 * @param rcac_rate_theta  PID+FF gains for the Rate Controller
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rcac_att_rate_variables_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t timestamp, uint8_t switch_att, uint8_t switch_rate, float alpha_pid_att, float alpha_pid_rate, float p11_att, float p11_ratex, const float *rcac_att_theta, const float *rcac_rate_theta)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, alpha_pid_att);
    _mav_put_float(buf, 12, alpha_pid_rate);
    _mav_put_float(buf, 16, p11_att);
    _mav_put_float(buf, 20, p11_ratex);
    _mav_put_uint8_t(buf, 84, switch_att);
    _mav_put_uint8_t(buf, 85, switch_rate);
    _mav_put_float_array(buf, 24, rcac_att_theta, 3);
    _mav_put_float_array(buf, 36, rcac_rate_theta, 12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN);
#else
    mavlink_rcac_att_rate_variables_t packet;
    packet.timestamp = timestamp;
    packet.alpha_pid_att = alpha_pid_att;
    packet.alpha_pid_rate = alpha_pid_rate;
    packet.p11_att = p11_att;
    packet.p11_ratex = p11_ratex;
    packet.switch_att = switch_att;
    packet.switch_rate = switch_rate;
    mav_array_memcpy(packet.rcac_att_theta, rcac_att_theta, sizeof(float)*3);
    mav_array_memcpy(packet.rcac_rate_theta, rcac_rate_theta, sizeof(float)*12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_MIN_LEN, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_CRC);
}

/**
 * @brief Pack a rcac_att_rate_variables message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param timestamp  Time since system start
 * @param switch_att  RCAC Att Controller switch
 * @param switch_rate  RCAC Rate Controller switch
 * @param alpha_pid_att  Gain multiplied by the PID attitude gains
 * @param alpha_pid_rate  Gain multiplied by the PID rate gains
 * @param p11_att  P(1,1) of the RCAC Attitude Controller
 * @param p11_ratex  P(1,1) of the RCAC Rate Controller
 * @param rcac_att_theta  P gains for the Attitude Controller
 * @param rcac_rate_theta  PID+FF gains for the Rate Controller
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rcac_att_rate_variables_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t timestamp,uint8_t switch_att,uint8_t switch_rate,float alpha_pid_att,float alpha_pid_rate,float p11_att,float p11_ratex,const float *rcac_att_theta,const float *rcac_rate_theta)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, alpha_pid_att);
    _mav_put_float(buf, 12, alpha_pid_rate);
    _mav_put_float(buf, 16, p11_att);
    _mav_put_float(buf, 20, p11_ratex);
    _mav_put_uint8_t(buf, 84, switch_att);
    _mav_put_uint8_t(buf, 85, switch_rate);
    _mav_put_float_array(buf, 24, rcac_att_theta, 3);
    _mav_put_float_array(buf, 36, rcac_rate_theta, 12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN);
#else
    mavlink_rcac_att_rate_variables_t packet;
    packet.timestamp = timestamp;
    packet.alpha_pid_att = alpha_pid_att;
    packet.alpha_pid_rate = alpha_pid_rate;
    packet.p11_att = p11_att;
    packet.p11_ratex = p11_ratex;
    packet.switch_att = switch_att;
    packet.switch_rate = switch_rate;
    mav_array_memcpy(packet.rcac_att_theta, rcac_att_theta, sizeof(float)*3);
    mav_array_memcpy(packet.rcac_rate_theta, rcac_rate_theta, sizeof(float)*12);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_MIN_LEN, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_CRC);
}

/**
 * @brief Encode a rcac_att_rate_variables struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param rcac_att_rate_variables C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rcac_att_rate_variables_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_rcac_att_rate_variables_t* rcac_att_rate_variables)
{
    return mavlink_msg_rcac_att_rate_variables_pack(system_id, component_id, msg, rcac_att_rate_variables->timestamp, rcac_att_rate_variables->switch_att, rcac_att_rate_variables->switch_rate, rcac_att_rate_variables->alpha_pid_att, rcac_att_rate_variables->alpha_pid_rate, rcac_att_rate_variables->p11_att, rcac_att_rate_variables->p11_ratex, rcac_att_rate_variables->rcac_att_theta, rcac_att_rate_variables->rcac_rate_theta);
}

/**
 * @brief Encode a rcac_att_rate_variables struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param rcac_att_rate_variables C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rcac_att_rate_variables_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_rcac_att_rate_variables_t* rcac_att_rate_variables)
{
    return mavlink_msg_rcac_att_rate_variables_pack_chan(system_id, component_id, chan, msg, rcac_att_rate_variables->timestamp, rcac_att_rate_variables->switch_att, rcac_att_rate_variables->switch_rate, rcac_att_rate_variables->alpha_pid_att, rcac_att_rate_variables->alpha_pid_rate, rcac_att_rate_variables->p11_att, rcac_att_rate_variables->p11_ratex, rcac_att_rate_variables->rcac_att_theta, rcac_att_rate_variables->rcac_rate_theta);
}

/**
 * @brief Send a rcac_att_rate_variables message
 * @param chan MAVLink channel to send the message
 *
 * @param timestamp  Time since system start
 * @param switch_att  RCAC Att Controller switch
 * @param switch_rate  RCAC Rate Controller switch
 * @param alpha_pid_att  Gain multiplied by the PID attitude gains
 * @param alpha_pid_rate  Gain multiplied by the PID rate gains
 * @param p11_att  P(1,1) of the RCAC Attitude Controller
 * @param p11_ratex  P(1,1) of the RCAC Rate Controller
 * @param rcac_att_theta  P gains for the Attitude Controller
 * @param rcac_rate_theta  PID+FF gains for the Rate Controller
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_rcac_att_rate_variables_send(mavlink_channel_t chan, uint64_t timestamp, uint8_t switch_att, uint8_t switch_rate, float alpha_pid_att, float alpha_pid_rate, float p11_att, float p11_ratex, const float *rcac_att_theta, const float *rcac_rate_theta)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN];
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, alpha_pid_att);
    _mav_put_float(buf, 12, alpha_pid_rate);
    _mav_put_float(buf, 16, p11_att);
    _mav_put_float(buf, 20, p11_ratex);
    _mav_put_uint8_t(buf, 84, switch_att);
    _mav_put_uint8_t(buf, 85, switch_rate);
    _mav_put_float_array(buf, 24, rcac_att_theta, 3);
    _mav_put_float_array(buf, 36, rcac_rate_theta, 12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES, buf, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_MIN_LEN, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_CRC);
#else
    mavlink_rcac_att_rate_variables_t packet;
    packet.timestamp = timestamp;
    packet.alpha_pid_att = alpha_pid_att;
    packet.alpha_pid_rate = alpha_pid_rate;
    packet.p11_att = p11_att;
    packet.p11_ratex = p11_ratex;
    packet.switch_att = switch_att;
    packet.switch_rate = switch_rate;
    mav_array_memcpy(packet.rcac_att_theta, rcac_att_theta, sizeof(float)*3);
    mav_array_memcpy(packet.rcac_rate_theta, rcac_rate_theta, sizeof(float)*12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES, (const char *)&packet, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_MIN_LEN, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_CRC);
#endif
}

/**
 * @brief Send a rcac_att_rate_variables message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_rcac_att_rate_variables_send_struct(mavlink_channel_t chan, const mavlink_rcac_att_rate_variables_t* rcac_att_rate_variables)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_rcac_att_rate_variables_send(chan, rcac_att_rate_variables->timestamp, rcac_att_rate_variables->switch_att, rcac_att_rate_variables->switch_rate, rcac_att_rate_variables->alpha_pid_att, rcac_att_rate_variables->alpha_pid_rate, rcac_att_rate_variables->p11_att, rcac_att_rate_variables->p11_ratex, rcac_att_rate_variables->rcac_att_theta, rcac_att_rate_variables->rcac_rate_theta);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES, (const char *)rcac_att_rate_variables, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_MIN_LEN, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_CRC);
#endif
}

#if MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_rcac_att_rate_variables_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t timestamp, uint8_t switch_att, uint8_t switch_rate, float alpha_pid_att, float alpha_pid_rate, float p11_att, float p11_ratex, const float *rcac_att_theta, const float *rcac_rate_theta)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, timestamp);
    _mav_put_float(buf, 8, alpha_pid_att);
    _mav_put_float(buf, 12, alpha_pid_rate);
    _mav_put_float(buf, 16, p11_att);
    _mav_put_float(buf, 20, p11_ratex);
    _mav_put_uint8_t(buf, 84, switch_att);
    _mav_put_uint8_t(buf, 85, switch_rate);
    _mav_put_float_array(buf, 24, rcac_att_theta, 3);
    _mav_put_float_array(buf, 36, rcac_rate_theta, 12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES, buf, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_MIN_LEN, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_CRC);
#else
    mavlink_rcac_att_rate_variables_t *packet = (mavlink_rcac_att_rate_variables_t *)msgbuf;
    packet->timestamp = timestamp;
    packet->alpha_pid_att = alpha_pid_att;
    packet->alpha_pid_rate = alpha_pid_rate;
    packet->p11_att = p11_att;
    packet->p11_ratex = p11_ratex;
    packet->switch_att = switch_att;
    packet->switch_rate = switch_rate;
    mav_array_memcpy(packet->rcac_att_theta, rcac_att_theta, sizeof(float)*3);
    mav_array_memcpy(packet->rcac_rate_theta, rcac_rate_theta, sizeof(float)*12);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES, (const char *)packet, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_MIN_LEN, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_CRC);
#endif
}
#endif

#endif

// MESSAGE RCAC_ATT_RATE_VARIABLES UNPACKING


/**
 * @brief Get field timestamp from rcac_att_rate_variables message
 *
 * @return  Time since system start
 */
static inline uint64_t mavlink_msg_rcac_att_rate_variables_get_timestamp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field switch_att from rcac_att_rate_variables message
 *
 * @return  RCAC Att Controller switch
 */
static inline uint8_t mavlink_msg_rcac_att_rate_variables_get_switch_att(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  84);
}

/**
 * @brief Get field switch_rate from rcac_att_rate_variables message
 *
 * @return  RCAC Rate Controller switch
 */
static inline uint8_t mavlink_msg_rcac_att_rate_variables_get_switch_rate(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  85);
}

/**
 * @brief Get field alpha_pid_att from rcac_att_rate_variables message
 *
 * @return  Gain multiplied by the PID attitude gains
 */
static inline float mavlink_msg_rcac_att_rate_variables_get_alpha_pid_att(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field alpha_pid_rate from rcac_att_rate_variables message
 *
 * @return  Gain multiplied by the PID rate gains
 */
static inline float mavlink_msg_rcac_att_rate_variables_get_alpha_pid_rate(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field p11_att from rcac_att_rate_variables message
 *
 * @return  P(1,1) of the RCAC Attitude Controller
 */
static inline float mavlink_msg_rcac_att_rate_variables_get_p11_att(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field p11_ratex from rcac_att_rate_variables message
 *
 * @return  P(1,1) of the RCAC Rate Controller
 */
static inline float mavlink_msg_rcac_att_rate_variables_get_p11_ratex(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field rcac_att_theta from rcac_att_rate_variables message
 *
 * @return  P gains for the Attitude Controller
 */
static inline uint16_t mavlink_msg_rcac_att_rate_variables_get_rcac_att_theta(const mavlink_message_t* msg, float *rcac_att_theta)
{
    return _MAV_RETURN_float_array(msg, rcac_att_theta, 3,  24);
}

/**
 * @brief Get field rcac_rate_theta from rcac_att_rate_variables message
 *
 * @return  PID+FF gains for the Rate Controller
 */
static inline uint16_t mavlink_msg_rcac_att_rate_variables_get_rcac_rate_theta(const mavlink_message_t* msg, float *rcac_rate_theta)
{
    return _MAV_RETURN_float_array(msg, rcac_rate_theta, 12,  36);
}

/**
 * @brief Decode a rcac_att_rate_variables message into a struct
 *
 * @param msg The message to decode
 * @param rcac_att_rate_variables C-struct to decode the message contents into
 */
static inline void mavlink_msg_rcac_att_rate_variables_decode(const mavlink_message_t* msg, mavlink_rcac_att_rate_variables_t* rcac_att_rate_variables)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    rcac_att_rate_variables->timestamp = mavlink_msg_rcac_att_rate_variables_get_timestamp(msg);
    rcac_att_rate_variables->alpha_pid_att = mavlink_msg_rcac_att_rate_variables_get_alpha_pid_att(msg);
    rcac_att_rate_variables->alpha_pid_rate = mavlink_msg_rcac_att_rate_variables_get_alpha_pid_rate(msg);
    rcac_att_rate_variables->p11_att = mavlink_msg_rcac_att_rate_variables_get_p11_att(msg);
    rcac_att_rate_variables->p11_ratex = mavlink_msg_rcac_att_rate_variables_get_p11_ratex(msg);
    mavlink_msg_rcac_att_rate_variables_get_rcac_att_theta(msg, rcac_att_rate_variables->rcac_att_theta);
    mavlink_msg_rcac_att_rate_variables_get_rcac_rate_theta(msg, rcac_att_rate_variables->rcac_rate_theta);
    rcac_att_rate_variables->switch_att = mavlink_msg_rcac_att_rate_variables_get_switch_att(msg);
    rcac_att_rate_variables->switch_rate = mavlink_msg_rcac_att_rate_variables_get_switch_rate(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN? msg->len : MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN;
        memset(rcac_att_rate_variables, 0, MAVLINK_MSG_ID_RCAC_ATT_RATE_VARIABLES_LEN);
    memcpy(rcac_att_rate_variables, _MAV_PAYLOAD(msg), len);
#endif
}
