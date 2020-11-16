//
//  PositionPlayback.hpp
//  morphingMouse
//
//  Created by Kosaku Namikawa on 2020/11/16.
//

#ifndef PositionPlayback_hpp
#define PositionPlayback_hpp

#include "ofMain.h"
#include "ofxCubicSpline.h"

class PositionPlayback {
public:
    enum PlaybackStatus {
        StandbyRecord,
        Recording,
        Playing,
        Stopping
    };
    
    enum MorphingMode {
        NoMorphing,
        Linear,
        CubicSprine
    };

    PositionPlayback();
  
    vector<glm::vec2> positions;
    vector<vector<glm::vec2>> recorded_positions;
    
    void update(const glm::vec2& recordedPosition = glm::vec2(0));
    
    void startRecord();
    void clearRecords();
    
    float getProgress() const;
    vector<glm::vec2> getCurrentPositions() const;
    PlaybackStatus getCurrentStatus() const;
    
    
private:
    unsigned int counter = 0;
    unsigned int duration = 120;
    
    PlaybackStatus status = Stopping;
    void morphPositions();
};

#endif /* PositionPlayback_hpp */
