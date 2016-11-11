/*
 * Copyright (C) Kimberly McGuire
 *
 * This file is part of paparazzi
 *
 */
/**
 * @file "modules/stereocam/stereocam2state/stereocam2state.h"
 * @author Kimberly McGuire
 * This module sends the data retreived from an external stereocamera modules, to the state filter of the drone. This is done so that the guidance modules can use that information for couadcopter
 */

#ifndef STEREOCAM2STATE_H
#define STEREOCAM2STATE_H

#include <std.h>
#include "modules/stereocam/stereocam.h"

extern void stereo_to_state_init(void);
extern void stereo_to_state_periodic(void);

extern int8_t win_x, win_y, win_radius, win_fitness;
extern int16_t nus_turn_cmd;
extern uint8_t pos_thresh, fit_thresh, max_cmd_div;

#endif

