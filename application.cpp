//
// Created by catag on 6/2/2022.
//

#include "application.h"

void application::setBoostList(std::vector<boost> boostList_) {
    boostList = boostList_;
}

void application::setFarmList(std::vector<autoFarmer> farmList_) {
    farmList = farmList_;
}

const std::vector<boost> &application::getBoostList() const {
    return boostList;
}

const std::vector<autoFarmer> &application::getFarmList() const {
    return farmList;
}

const std::vector<std::shared_ptr<profileMinimal>> &application::getProfileList() const {
    return profileList;
}

void application::setProfileList(std::vector<std::shared_ptr<profileMinimal>> profileList_) {
    profileList = profileList_;
}

const std::shared_ptr<profileMinimal> &application::getCurrentProfile() const {
    return currentProfile;
}

void application::setCurrentProfile(std::shared_ptr<profileMinimal> currentProfile_) {
    currentProfile = currentProfile_;
}

void application::addToProfileList(std::shared_ptr<profileMinimal> profile) {
    profileList.push_back(profile->clone());
}

