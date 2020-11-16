//
//  PositionPlayback.hpp
//  morphingMouse
//
//  Created by Kosaku Namikawa on 2020/11/16.
//

#ifndef PositionPlayback_hpp
#define PositionPlayback_hpp

#include "ofMain.h"

class PositionPlayback {
public:
    enum PlaybackStatus {
        StandbyRecord,
        Recording,
        Playing,
        Stopping
    };

    PositionPlayback();
  
    vector<glm::vec2> positions;
    float getProgress() const;
    void update(const glm::vec2& recordedPosition = glm::vec2(0));
    void startRecord();
    glm::vec2 getCurrentPos() const;
    PlaybackStatus getCurrentStatus() const;
private:
    unsigned int counter = 0;
    unsigned int duration = 120;
    
    PlaybackStatus status = Stopping;
};

#endif /* PositionPlayback_hpp */