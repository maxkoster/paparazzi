/*
 * Copyright (C) Kimberly McGuire
 *
 * This file is part of paparazzi
 *
 */
/**
 * @file "modules/stereocam/stereocam2state/stereocam2state.c"
 * @author Kimberly McGuire
 * This module sends the data retreived from an external stereocamera modules, to the state filter of the drone. This is done so that the guidance modules can use that information for couadcopter
 */

#include "modules/stereocam/stereocam2state/stereocam2state.h"

#include "subsystems/abi.h"
#include "subsystems/datalink/telemetry.h"

#include "paparazzi.h"

#ifndef STEREOCAM2STATE_SENDER_ID
#define STEREOCAM2STATE_SENDER_ID ABI_BROADCAST
#endif

#ifndef STEREOCAM2STATE_RECEIVED_DATA_TYPE
#define STEREOCAM2STATE_RECEIVED_DATA_TYPE 0
#endif

int8_t win_x, win_y, win_radius, win_fitness=111;
int16_t nus_turn_cmd=0;
uint8_t pos_thresh=5;
uint8_t fit_thresh=30;
uint8_t max_cmd_div=2;


static void send_stereo_data(struct transport_tx *trans, struct link_device *dev)
 {
   pprz_msg_send_STEREO_DATA(trans, dev, AC_ID,
                         &win_x, &win_y,
                         &win_radius, &win_fitness);
 }

void stereocam_to_state(void);

void stereo_to_state_init(void)
{
	register_periodic_telemetry(DefaultPeriodic, PPRZ_MSG_ID_STEREO_DATA, send_stereo_data);
}

void stereo_to_state_periodic(void)
{
  if (stereocam_data.fresh && stereocam_data.len == 4) { // length of NUS window detection code
	int8_t* pointer=stereocam_data.data; // to transform uint8 message back to int8

	win_x = pointer[0];
    win_y = pointer[1];
    win_radius = pointer[2];
    win_fitness = pointer[3];
    stereocam_data.fresh = 0;

    if (win_x>pos_thresh && win_radius > fit_thresh){
  	  nus_turn_cmd=MAX_PPRZ/max_cmd_div;
    }
    else if (win_x<-pos_thresh && win_radius > fit_thresh){
  	  nus_turn_cmd=-MAX_PPRZ/max_cmd_div;
    }
    else{
  	  nus_turn_cmd=0;
    }
  }
}

//void stereocam_to_state(void)
//{
//
//  // Get info from stereocam data
//  // 0 = stereoboard's #define SEND_EDGEFLOW
//#if STEREOCAM2STATE_RECEIVED_DATA_TYPE == 0
//  // opticflow
//  int16_t div_x = (int16_t)stereocam_data.data[0] << 8;
//  div_x |= (int16_t)stereocam_data.data[1];
//  int16_t flow_x = (int16_t)stereocam_data.data[2] << 8;
//  flow_x |= (int16_t)stereocam_data.data[3];
//  int16_t div_y = (int16_t)stereocam_data.data[4] << 8;
//  div_y |= (int16_t)stereocam_data.data[5];
//  int16_t flow_y = (int16_t)stereocam_data.data[6] << 8;
//  flow_y |= (int16_t)stereocam_data.data[7];
//
//  float fps = (float)stereocam_data.data[9];
//  //int8_t agl = stereocam_data.data[8]; // in cm
//
//  // velocity
//  int16_t vel_x_int = (int16_t)stereocam_data.data[10] << 8;
//  vel_x_int |= (int16_t)stereocam_data.data[11];
//  int16_t vel_y_int = (int16_t)stereocam_data.data[12] << 8;
//  vel_y_int |= (int16_t)stereocam_data.data[13];
//
//  int16_t RES = 100;
//
//  float vel_x = (float)vel_x_int / RES;
//  float vel_y = (float)vel_y_int / RES;
//
//  // Derotate velocity and transform from frame to body coordinates
//  // TODO: send resolution directly from stereocam
//
//  float vel_body_x = - vel_x;
//  float vel_body_y = vel_y;
//
//  //Send velocity estimate to state
//  //TODO:: Make variance dependable on line fit error, after new horizontal filter is made
//  uint32_t now_ts = get_sys_time_usec();
//
//  if (!(abs(vel_body_x) > 0.5 || abs(vel_body_x) > 0.5))
//  {
//    AbiSendMsgVELOCITY_ESTIMATE(STEREOCAM2STATE_SENDER_ID, now_ts,
//                                vel_body_x,
//                                vel_body_y,
//                                0.0f,
//                                0.3f
//                               );
//  }
//
//  // Reusing the OPTIC_FLOW_EST telemetry messages, with some values replaced by 0
//
//  uint16_t dummy_uint16 = 0;
//  int16_t dummy_int16 = 0;
//  float dummy_float = 0;
//
//  DOWNLINK_SEND_OPTIC_FLOW_EST(DefaultChannel, DefaultDevice, &fps, &dummy_uint16, &dummy_uint16, &flow_x, &flow_y, &dummy_int16, &dummy_int16,
//		  &vel_x, &vel_y,&dummy_float, &dummy_float, &dummy_float);
//
//#endif
//
//}
