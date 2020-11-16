//
//  PositionPlayback.cpp
//  morphingMouse
//
//  Created by Kosaku Namikawa on 2020/11/16.
//

#include "PositionPlayback.hpp"


PositionPlayback::PositionPlayback() {
    positions.resize(duration, glm::vec2(ofGetWidth() * 0.5, ofGetHeight() * 0.5));
}


void PositionPlayback::update(const glm::vec2& recordedPosition) {
    // 再生位置更新
    counter = (counter + 1) % duration;
    
    // 録画終了判定
    if (counter == 0  && status == PlaybackStatus::Recording) {
        status = PlaybackStatus::Playing;
    }
    
    // 録画開始
    if (counter == 0 && status == PlaybackStatus::StandbyRecord) {
        cout << "recording" << endl;
        status = PlaybackStatus::Recording;
    }
    
    // 録画処理
    if (status == PlaybackStatus::Recording) {
        positions[counter] = recordedPosition;
        morphPositions();
    }
}

void PositionPlayback::startRecord() {
    cout << "standby" << endl;
    status = PlaybackStatus::StandbyRecord;
}

void PositionPlayback::morphPositions() {
    ofxCubicSpline cubic_x, cubic_y;
    
    const int morph_duration = 10;
    
    vector<glm::vec2> input_x;
    input_x.push_back(glm::vec2(-1, positions[duration - 11].x));
    input_x.push_back(glm::vec2(0, positions[duration - 10].x));
    input_x.push_back(glm::vec2(10, positions[0].x));
    
    vector<glm::vec2> input_y;
    input_y.push_back(glm::vec2(-1, positions[duration - 11].y));
    input_y.push_back(glm::vec2(0, positions[duration - 10].y));
    input_y.push_back(glm::vec2(10, positions[0].y));
    
    cubic_x.setData(input_x);
    cubic_y.setData(input_y);
    
    auto diff = (positions[0] - positions[duration-morph_duration]) / morph_duration;
    
    
    for (auto i = 0; i < morph_duration; i++) {
        positions[i+duration-morph_duration] = glm::vec2(cubic_x.at(i), cubic_y.at(i));
//        positions[i+duration-morph_duration] = positions[duration - morph_duration] + diff * i;
    }
}

glm::vec2 PositionPlayback::getCurrentPos() const {
    return positions[counter];
}

float PositionPlayback::getProgress() const {
    return (float) counter / duration;
}

PositionPlayback::PlaybackStatus PositionPlayback::getCurrentStatus() const {
    return status;
};
