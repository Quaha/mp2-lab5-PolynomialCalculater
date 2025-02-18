#include <gtest/gtest.h>

#include "includes.hpp"

#include "Automat.hpp"

TEST(Automat, canCreateAutomat) {
    ASSERT_NO_THROW(Automat automat);
}

TEST(Automat, canAddAndCheckNextState) {
    Automat automat;

    int start_state = 0;
    char transition_char = 'a';
    int new_status = INTEGER;

    ASSERT_NO_THROW(automat.createNextState(start_state, transition_char, new_status));
    EXPECT_TRUE(automat.nextStateExist(start_state, transition_char));
}

TEST(Automat, nextStateDoesNotExistByDefault) {
    Automat automat;

    EXPECT_EQ(automat.nextStateExist(0, 'x'), false);
}

TEST(Automat, canTransitionToNextState) {
    Automat automat;

    int start_state = 0;
    char transition_char = 'a';
    int new_status = REAL;

    automat.createNextState(start_state, transition_char, new_status);

    EXPECT_EQ(automat.getNextState(start_state, transition_char), 1);
}

TEST(Automat, canGetStatusOfState) {
    Automat automat;

    int start_state = 0;
    char transition_char = 'a';
    int new_status = VARIABLE;

    automat.createNextState(start_state, transition_char, new_status);

    int next_state = automat.getNextState(start_state, transition_char);
    EXPECT_EQ(automat.getStatus(next_state), VARIABLE);
}

TEST(Automat, invalidTransition) {
    Automat automat;

    int start_state = 0;
    char invalid_char = 'z';

    ASSERT_ANY_THROW(automat.getNextState(start_state, invalid_char));
}

TEST(Automat, canCreateNewState) {
    Automat automat;

    int new_status = FUNCTION;

    ASSERT_NO_THROW(automat.createNewState(new_status));
    EXPECT_EQ(automat.getStatus(1), FUNCTION);
}

TEST(Automat, canAddTransitionBetweenStates) {
    Automat automat;

    int start_status = INTEGER;
    int next_status = REAL;

    automat.createNewState(start_status);
    automat.createNewState(next_status);

    int start_state = 1;
    int next_state = 2;
    char transition_char = 'x';

    ASSERT_NO_THROW(automat.addTransition(start_state, next_state, transition_char));
    EXPECT_TRUE(automat.nextStateExist(start_state, transition_char));
    EXPECT_EQ(automat.getNextState(start_state, transition_char), next_state);
}

TEST(Automat, invalidStateInAddTransition) {
    Automat automat;

    automat.createNewState(INTEGER);

    int start_state = 1;
    int invalid_state = 99;
    char transition_char = 'x';

    ASSERT_ANY_THROW(automat.addTransition(start_state, invalid_state, transition_char));
    ASSERT_ANY_THROW(automat.addTransition(invalid_state, start_state, transition_char));
}

TEST(Automat, throws_on_duplicate_transition) {
    Automat automat;

    automat.createNewState(INTEGER);
    automat.createNewState(REAL);

    int start_state = 1;
    int next_state = 2;
    char transition_char = 'y';

    automat.addTransition(start_state, next_state, transition_char);

    ASSERT_ANY_THROW(automat.addTransition(start_state, next_state, transition_char));
}
