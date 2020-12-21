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
        morphPositions();
        
        recorded_positions.push_back(move(positions));
        positions.clear();
        positions = vector<glm::vec2>(duration);
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

void PositionPlayback::startRecord() {
    cout << "standby" << endl;
    status = PlaybackStatus::StandbyRecord;
}

void PositionPlayback::clearRecords() {
    recorded_positions.clear();
}

void PositionPlayback::morphPositions() {
    ofxCubicSpline cubic_x, cubic_y;
    
    vector<glm::vec2> input_x;
    input_x.push_back(glm::vec2(-1, positions[duration - morph_duration - 1].x));
    input_x.push_back(glm::vec2(0, positions[duration - morph_duration].x));
    input_x.push_back(glm::vec2(morph_duration, positions[0].x));
    input_x.push_back(glm::vec2(morph_duration + 1, positions[1].x));
    
    vector<glm::vec2> input_y;
    input_y.push_back(glm::vec2(-1, positions[duration - morph_duration - 1].y));
    input_y.push_back(glm::vec2(0, positions[duration - morph_duration].y));
    input_y.push_back(glm::vec2(morph_duration, positions[0].y));
    input_y.push_back(glm::vec2(morph_duration + 1, positions[1].y));
    
    cubic_x.setData(input_x);
    cubic_y.setData(input_y);
    
    auto diff = (positions[0] - positions[duration-morph_duration]) / morph_duration;
    
    
    for (auto i = 0; i < morph_duration; i++) {
        positions[i+duration-morph_duration] = glm::vec2(cubic_x.at(i), cubic_y.at(i));
//        positions[i+duration-morph_duration] = positions[duration - morph_duration] + diff * i;
    }
}

vector<glm::vec2> PositionPlayback::getCurrentPositions() const {
    vector<glm::vec2> tmp(recorded_positions.size());
    transform(recorded_positions.begin(), recorded_positions.end(), tmp.begin(), [&](const vector<glm::vec2> positions) {return positions[counter];});
    
    return move(tmp);
}

void PositionPlayback::setMorphDuration(int duration) {
    morph_duration = duration;
}

float PositionPlayback::getProgress() const {
    return (float) counter / duration;
}

PositionPlayback::PlaybackStatus PositionPlayback::getCurrentStatus() const {
    return status;
};
