/*
 * Copyright 2021 Benjamin Edgington
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h> // rand()
#include "test_util.h"

void generate_trusted_setup(g1_t *s1, g2_t *s2, const scalar_t *secret, const uint64_t n) {
    fr_t s_pow, s;
    fr_from_scalar(&s, secret);
    s_pow = fr_one;

    for (uint64_t i = 0; i < n; i++) {
        g1_mul(s1 + i, &g1_generator, &s_pow);
        g2_mul(s2 + i, &g2_generator, &s_pow);
        fr_mul(&s_pow, &s_pow, &s);
    }
}

uint64_t rand_uint64() {
    uint64_t a = (uint64_t)rand();
    uint64_t b = (uint64_t)rand();
    return a << 32 | b;
}

fr_t rand_fr() {
    fr_t ret;
    uint64_t a[4];
    a[0] = rand_uint64();
    a[1] = rand_uint64();
    a[2] = rand_uint64();
    a[3] = rand_uint64();
    fr_from_uint64s(&ret, a);
    return ret;
}

g1_t rand_g1() {
    g1_t ret;
    fr_t random = rand_fr();
    g1_mul(&ret, &g1_generator, &random);
    return ret;
}

// Dummy function used to get the test-suite to print a title
void title(void) {}