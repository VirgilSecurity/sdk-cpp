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

# Settings
REPO_PATH=git@github.com:VirgilSecurity/virgil-cpp.git
HTML_PATH_SRC="${TRAVIS_BUILD_DIR}/virgil.sdk.keys/docs/html"
HTML_PATH_DST="${TRAVIS_BUILD_DIR}/${BUILD_DIR_NAME}/virgil.sdk.keys/docs/html"
COMMIT_USER="Travis CI documentation builder."
COMMIT_EMAIL="sergey.seroshtan@gmail.com"
CHANGESET=$(git rev-parse --verify HEAD)

# Get a clean version of the HTML documentation repo.
rm -rf ${HTML_PATH_DST}
mkdir -p ${HTML_PATH_DST}
git clone -b gh-pages "${REPO_PATH}" --single-branch ${HTML_PATH_DST}

# rm all the files through git to prevent stale files.
cd ${HTML_PATH_DST}
git rm -rf .
cd -

# Generate the HTML documentation.
cd "${TRAVIS_BUILD_DIR}/${BUILD_DIR_NAME}"
make doc
cd -

# Copy new documentation
cp -Rf "${HTML_PATH_SRC}" "${HTML_PATH_DST}"

# Create and commit the documentation repo.
cd ${HTML_PATH_DST}
git add .
git config user.name "${COMMIT_USER}"
git config user.email "${COMMIT_EMAIL}"
git commit -m "Automated documentation build for changeset ${CHANGESET}."
git push origin gh-pages
cd -
