/*
 * $Id: error.h 1519 2009-04-22 23:12:44Z rfhh $
 *
 * Copyright (C) 2009, Rutger Hofman, VU Amsterdam
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 */

#ifndef URJ_ERROR_H
#define URJ_ERROR_H

#include <stdio.h>

/**
 * Error types
 */
typedef enum urj_error {
    URJ_ERROR_OK        = 0,
    URJ_ERROR_ALREADY,
    URJ_ERROR_OUT_OF_MEMORY,
    URJ_ERROR_NO_ACTIVE_PART,
    URJ_ERROR_INVALID,
    URJ_ERROR_NOTFOUND,
    URJ_ERROR_IO,                               /**< I/O error from OS */
} urj_error_t;

/** Max length of message string that can be recorded. */
#define URJ_ERROR_MSG_LEN       256

/**
 * Error state.
 */
typedef struct urj_error_state {
    urj_error_t         errnum;                 /**< error number */
    const char         *file;                   /**< file where error is set */
    const char         *function;               /**< function --,,-- */
    int                 line;                   /**< line no --,,-- */
    char                msg[URJ_ERROR_MSG_LEN]; /**< printf-style message */
} urj_error_state_t;

extern urj_error_state_t        urj_error_state;

/**
 * Set error state. The macro interface allows for a stack of errors, where
 * this macro would push an error. The implementation is free to maintain
 * a stack of depth one.
 *
 * @param e urj_error_t value
 * @param ... consists of a printf argument set. It needs to start with a
 *      const char *fmt, followed by arguments used by fmt.
 */
#define urj_error_set(e, ...) \
    do { \
        urj_error_state.errnum = e; \
        urj_error_state.file = __FILE__; \
        urj_error_state.function = __func__; \
        urj_error_state.line = __LINE__; \
        snprintf (urj_error_state.msg, sizeof urj_error_state.msg, \
                  __VA_ARGS__); \
    } while (0)

/**
 * The top of the error stack. The caller must not modify the returned struct.
 */
const urj_error_state_t *urj_error_get(void);
/**
 * Pop the top off the error stack.
 * @return #URJ_ERROR_OK if the bottom of the error stack is reached
 */
urj_error_t urj_error_get_reset(void);
/**
 * The top of the error state in human-readable form.
 *
 * This function is not reentrant.
 *
 * @return a pointer to a static area.
 */
const char *urj_error_describe(void);

#endif /* URJ_ERROR_H */