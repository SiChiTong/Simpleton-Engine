//
//  grid.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_grid_grid_hpp
#define engine_grid_grid_hpp

#include <vector>
#include <glm/vec2.hpp>

namespace Grid {
  using Coord = unsigned;
  using Pos = glm::tvec2<Coord>;

  template <typename Tile_>
  class Grid {
  public:
    using Tile = Tile_;
    using Tiles = std::vector<Tile>;
  
    Grid(Grid &&) = default;
    Grid &operator=(Grid &&) = default;
  
    Grid()
      : mSize(0, 0) {}
    explicit Grid(const Pos size, const Tile &tile = {})
      : mTiles(size.x * size.y, tile), mSize(size) {}
    
    void clear() {
      mTiles.clear();
      mSize = {0, 0};
    }
    void resize(const Pos size, const Tile &tile = {}) {
      mTiles.resize(size.x * size.y, tile);
      mSize = size;
    }
    void fill(const Tile &tile) {
      std::fill(mTiles.begin(), mTiles.end(), tile);
    }
    
    auto begin() {
      return mTiles.begin();
    }
    auto begin() const {
      return mTiles.begin();
    }
    auto cbegin() const {
      return mTiles.begin();
    }
    auto end() {
      return mTiles.end();
    }
    auto end() const {
      return mTiles.end();
    }
    auto cend() const {
      return mTiles.end();
    }
    
    Pos size() const {
      return mSize;
    }
    Coord width() const {
      return mSize.x;
    }
    Coord height() const {
      return mSize.y;
    }
    size_t area() const {
      return mTiles.size();
    }
    
    bool outOfRange(const Pos pos) const {
      return pos.x >= mSize.x || pos.y >= mSize.y;
    }
    bool outOfRange(const size_t index) const {
      return index >= mTiles.size();
    }
    
    size_t toIndex(const Pos pos) const {
      return pos.y * mSize.x + pos.x;
    }
    Pos toPos(const size_t index) const {
      const Coord cindex = static_cast<Coord>(index);
      return {cindex % mSize.x, cindex / mSize.x};
    }
    
    Tile &operator[](const Pos pos) {
      return mTiles[toIndex(pos)];
    }
    const Tile &operator[](const Pos pos) const {
      return mTiles[toIndex(pos)];
    }
    Tile &at(const Pos pos) {
      checkRange(pos);
      return mTiles[toIndex(pos)];
    }
    const Tile &at(const Pos pos) const {
      checkRange(pos);
      return mTiles[toIndex(pos)];
    }
    
    Tile &operator[](const size_t index) {
      return mTiles[index];
    }
    const Tile &operator[](const size_t index) const {
      return mTiles[index];
    }
    Tile &at(const size_t index) {
      checkRange(index);
      return mTiles[index];
    }
    const Tile &at(const size_t index) const {
      checkRange(index);
      return mTiles[index];
    }
  
  private:
    Tiles mTiles;
    Pos mSize;
    
    void checkRange(const Pos pos) const {
      if (outOfRange(pos)) {
        throw std::range_error("Position out of range");
      }
    }
    void checkRange(const size_t index) const {
      if (outOfRange(index)) {
        throw std::range_error("Index out of range");
      }
    }
  };
}

#endif