#!/bin/bash
#
# Copyright (C) 2015 Virgil Security Inc.
#
# Lead Maintainer: Virgil Security Inc. <support@virgilsecurity.com>
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#     (1) Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#
#     (2) Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in
#     the documentation and/or other materials provided with the
#     distribution.
#
#     (3) Neither the name of the copyright holder nor the names of its
#     contributors may be used to endorse or promote products derived from
#     this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
# IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

set -ev

cd "${TRAVIS_BUILD_DIR}/${BUILD_DIR_NAME}"

if [ "${PUBLISH_DOCS}" == "ON" ]; then
    # Generate the HTML documentation.
    make doc-sdk-public-keys
    make doc-sdk-private-keys
fi

if [ "${PUBLISH_COVERITY_SCAN}" == "ON" ] && [ "${TRAVIS_BRANCH}" == "coverity_scan" ] && [ "${CC}" == "gcc-4.8" ]; then
    # Build for Coverity Scan.
    export COVERITY_SCAN_PROJECT_NAME="VirgilSecurity/virgil-sdk-cpp"
    export COVERITY_SCAN_BRANCH_PATTERN="coverity_scan"
    export COVERITY_SCAN_NOTIFICATION_EMAIL="sergey.seroshtan@gmail.com"
    export COVERITY_SCAN_BUILD_COMMAND="make -j2"

    # Run Coverity Scan build
    curl -s "https://scan.coverity.com/scripts/travisci_build_coverity_scan.sh"                          | \
        sed 's/\(# Build\)/# Configure\ncov-configure --compiler \`which ${CC}\` --comptype gcc\n\n\1/g' | \
        bash

    cat ./cov-int/build-log.txt | true
    cat ./cov-int/scm_log.txt   | true
else
    # Build
    make -j2 VERBOSE=1
    ctest --verbose
    make install
fi
