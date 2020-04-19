//
// Created by Teresa Dong on 4/17/20.
//

#include "mylibrary/tetromino.h"

#include <ctime>

namespace mylibrary {

Tetromino::Tetromino(int center_tile) {
  //Generate a random number quickly: 0-6
  //Credit: https://stackoverflow.com/questions/20201141/same-random-numbers-generated-every-time-in-c
  //Answered by rkyser
  struct timespec ts{};
  clock_gettime(CLOCK_MONOTONIC, &ts);

  /* using nano-seconds instead of seconds */
  srand((time_t)ts.tv_nsec);
  tetromino_type_ = kTetrominoTypes[rand() % kNumTetrominoTypes];
  InitializePixels_(center_tile);
}

void Tetromino::InitializePixels_(int center_tile) {
  switch (tetromino_type_) {
    case TetrominoType::kZ:
      GenerateZ(center_tile);
      break;
    case TetrominoType::kS:
      GenerateS(center_tile);
      break;
    case TetrominoType::kT:
      GenerateT(center_tile);
      break;
    case TetrominoType::kO:
      GenerateO(center_tile);
      break;
    case TetrominoType::kL:
      GenerateL(center_tile);
      break;
    case TetrominoType::kJ:
      GenerateJ(center_tile);
      break;
    case TetrominoType::kI:
      GenerateI(center_tile);
      break;
  }
}

void Tetromino::GenerateZ(int center_tile) {
  pixels[0] = {center_tile - 1, 0};
  pixels[1] = {center_tile, 0};
  pixels[2] = {center_tile, 1};
  pixels[3] = {center_tile + 1, 1};
}

void Tetromino::GenerateS(int center_tile) {
  pixels[0] = {center_tile - 1, 1};
  pixels[1] = {center_tile, 1};
  pixels[2] = {center_tile, 0};
  pixels[3] = {center_tile + 1, 0};
}

void Tetromino::GenerateT(int center_tile) {
  pixels[0] = {center_tile - 1, 0};
  pixels[1] = {center_tile, 0};
  pixels[2] = {center_tile + 1, 0};
  pixels[3] = {center_tile, 1};
}

void Tetromino::GenerateO(int center_tile) {
  pixels[0] = Location(center_tile - 1, 0);
  pixels[1] = Location(center_tile, 0);
  pixels[2] = Location(center_tile - 1, 1);
  pixels[3] = Location(center_tile, 1);
}

void Tetromino::GenerateI(int center_tile) {
  pixels[0] = Location(center_tile, 0);
  pixels[1] = Location(center_tile, 1);
  pixels[2] = Location(center_tile, 2);
  pixels[3] = Location(center_tile, 3);
}

void Tetromino::GenerateJ(int center_tile) {
  pixels[0] = Location(center_tile, 0);
  pixels[1] = Location(center_tile, 1);
  pixels[2] = Location(center_tile, 2);
  pixels[3] = Location(center_tile - 1, 2);
}

void Tetromino::GenerateL(int center_tile) {
  pixels[0] = Location(center_tile, 0);
  pixels[1] = Location(center_tile, 1);
  pixels[2] = Location(center_tile, 2);
  pixels[3] = Location(center_tile + 1, 2);
}

Location Tetromino::GetPixelLocation(size_t index) {
  return pixels[index];
}

void Tetromino::SetPixelLocation(size_t index, Location loc) {
  pixels[index] = loc;
}

std::vector<int> Tetromino::FindContactPixels() {
  //TODO: Implement global contact indexes variable so that if the pixels have't been rotated, we can just return the same thing.
  std::vector<int> contact_indexes;
  std::vector<int> checked_indexes;
  for (int i = 0; i < 4; i++) {
    //Check if we have already evaluates this pixel
    if (std::find(checked_indexes.begin(), checked_indexes.end(), i) != checked_indexes.end()) {
      continue;
    }

    //Else add it to our checked indexes
    checked_indexes.push_back(i);
    Location contact_pixel = pixels[i];
    size_t pixel_index = i;

    for (int j = i; j < 4; j++) {
      if (pixels[j].Row() == contact_pixel.Row()) {
        //We've checked this pixel now, regardless if it's the contact or not
        checked_indexes.push_back(j);
        if (pixels[j].Col() > contact_pixel.Col()) {
          contact_pixel = pixels[j];
          pixel_index = j;
        }
      }
    }

    //Add this row's contact pixel into our vector
    contact_indexes.push_back(pixel_index);
  }

  return contact_indexes;
}

}