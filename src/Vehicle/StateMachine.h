/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

class StateMachine
{
public:
    typedef void (*StateFn)(StateMachine* stateMachine);

    StateMachine(void);

    /// Start the state machine with the first step
    void start(void);

    /// Advance the state machine to the next state and call the state function
    void advance(void);

    /// Move the state machine to the specified state and call the state function
    void move(StateFn stateFn);

    /// @return The number of states in the rgStates array
    virtual int stateCount(void) const = 0;

    /// @return Array of states to execute
    virtual const StateFn* rgStates(void) const = 0;

    /// Called when all states have completed
    virtual void statesCompleted(void) const;

protected:
    bool    _active = false;
    int     _stateIndex  = -1;
};
