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
    }
}

glm::vec2 PositionPlayback::getCurrentPos() const {
    return positions[counter];
}

void PositionPlayback::startRecord() {
    cout << "standby" << endl;
    status = PlaybackStatus::StandbyRecord;
}

float PositionPlayback::getProgress() const {
    return (float) counter / duration;
}

PositionPlayback::PlaybackStatus PositionPlayback::getCurrentStatus() const {
    return status;
};
