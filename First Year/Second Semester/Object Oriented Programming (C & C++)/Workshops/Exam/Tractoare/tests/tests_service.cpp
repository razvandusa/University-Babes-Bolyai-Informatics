#include "tests_service.h"

#include <assert.h>
#include <iostream>

#include "../headers/domain.h"
#include "../headers/repository.h"
#include "../headers/service.h"

static void test_add_tractor() {
    Repository repository("/Users/razvandusa/CLionProjects/Tractoare/tests/tests_input.txt");
    Service service (repository);

    try {
        service.add_tractor("1", "test", "test", "6");
        assert(true);   
    } catch (...) {
        assert(false);
    }

    try {
        service.add_tractor("1", "test", "test", "10");
        assert(false);
    } catch (...) {
        assert(true);
    }

    try {
        service.add_tractor("a", "test", "test", "10");
        assert(false);
    } catch (...) {
        assert(true);
    }

    try {
        service.add_tractor("1", "test", "test", "b");
        assert(false);
    } catch (...) {
        assert(true);
    }

    try {
        service.add_tractor("1", "test", "test", "3");
        assert(false);
    } catch (...) {
        assert(true);
    }

    try {
        service.add_tractor("1", "test", "test", "20");
        assert(false);
    } catch (...) {
        assert(true);
    }

    try {
        service.add_tractor("", "test", "test", "10");
        assert(false);
    } catch (...) {
        assert(true);
    }

    try {
        service.add_tractor("1", "", "test", "10");
        assert(false);
    } catch (...) {
        assert(true);
    }

    try {
        service.add_tractor("1", "test", "", "10");
        assert(false);
    } catch (...) {
        assert(true);
    }

    try {
        service.add_tractor("1", "test", "test", "");
        assert(false);
    } catch (...) {
        assert(true);
    }
}

void tests_service() {
    test_add_tractor();
}