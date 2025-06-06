#include "screen_recorder.h"
#include "ffmpeg_wrapper.h"
#include "real_time_effects.h"
#include <iostream>

namespace my_streaming_software {
namespace recorder {

void ScreenRecorder::startRecording(const std::string& filePath) {
    if (isRecording) {
        std::cerr << "Recording is already in progress." << std::endl;
        return;
    }

    this->filePath = filePath;
    isRecording = true;

    // Initialize FFmpeg and start recording
    if (!ffmpegWrapper.initialize(filePath)) {
        std::cerr << "Failed to initialize FFmpeg." << std::endl;
        isRecording = false;
        return;
    }

    if (!ffmpegWrapper.start()) {
        std::cerr << "Failed to start recording." << std::endl;
        isRecording = false;
        return;
    }

    std::cout << "Recording started." << std::endl;
}

void ScreenRecorder::stopRecording() {
    if (!isRecording) {
        std::cerr << "No recording is in progress." << std::endl;
        return;
    }

    // Stop FFmpeg recording
    if (!ffmpegWrapper.stop()) {
        std::cerr << "Failed to stop recording." << std::endl;
        return;
    }

    isRecording = false;
    std::cout << "Recording stopped." << std::endl;
}

void ScreenRecorder::saveRecording() {
    if (isRecording) {
        std::cerr << "Cannot save while recording is in progress." << std::endl;
        return;
    }

    // Save the recorded file
    if (!ffmpegWrapper.save(filePath)) {
        std::cerr << "Failed to save recording." << std::endl;
        return;
    }

    std::cout << "Recording saved to " << filePath << std::endl;
}

void ScreenRecorder::applyRealTimeEffect(const std::string& effectName) {
    if (!isRecording) {
        std::cerr << "Cannot apply effects while recording is not in progress." << std::endl;
        return;
    }

    // Apply real-time effect using FFmpeg
    if (!ffmpegWrapper.applyRealTimeEffect(effectName)) {
        std::cerr << "Failed to apply real-time effect: " << effectName << std::endl;
        return;
    }

    std::cout << "Real-time effect " << effectName << " applied." << std::endl;
}

} // namespace recorder
} // namespace my_streaming_software
