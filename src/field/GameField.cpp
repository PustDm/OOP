#include "GameField.h"

GameField::GameField(int width, int height, std::size_t maxUnits)
    : width_(width), height_(height), maxUnits_(maxUnits),
      grid_(static_cast<std::size_t>(width) * height) {
    if (width <= 0 || height <= 0)
        throw std::invalid_argument("Width and height must be positive");
    if (maxUnits_ == 0)
        throw std::invalid_argument("maxUnits must be positive");
}

GameField::GameField(const GameField& other)
    : width_(other.width_), height_(other.height_),
      maxUnits_(other.maxUnits_), grid_(other.grid_.size()) {
    for (std::size_t i = 0; i < other.grid_.size(); ++i) {
        if (other.grid_[i]) grid_[i] = other.grid_[i]->clone();
    }
}

GameField& GameField::operator=(const GameField& other) {
    if (this == &other) return *this;
    GameField tmp(other);           // copy-and-swap
    std::swap(width_,    tmp.width_);
    std::swap(height_,   tmp.height_);
    std::swap(maxUnits_, tmp.maxUnits_);
    std::swap(grid_,     tmp.grid_);
    return *this;
}

GameField::GameField(GameField&& other) noexcept
    : width_(other.width_), height_(other.height_),
      maxUnits_(other.maxUnits_), grid_(std::move(other.grid_)) {
    other.width_ = 0;
    other.height_ = 0;
    other.maxUnits_ = 0;
}

GameField& GameField::operator=(GameField&& other) noexcept {
    if (this == &other) return *this;
    width_    = other.width_;
    height_   = other.height_;
    maxUnits_ = other.maxUnits_;
    grid_     = std::move(other.grid_);

    other.width_ = 0;
    other.height_ = 0;
    other.maxUnits_ = 0;
    return *this;
}

void GameField::addUnit(std::unique_ptr<Unit> unit, int x, int y) {
    if (!unit) throw std::invalid_argument("Unit is null");
    std::size_t idx = index(x, y);
    if (grid_[idx]) throw std::runtime_error("Cell is occupied");
    if (countUnits() >= maxUnits_)
        throw std::runtime_error("Field is full (maxUnits reached)");

    unit->move(x, y);
    grid_[idx] = std::move(unit);
}

void GameField::removeUnit(int x, int y) {
    std::size_t idx = index(x, y);
    if (!grid_[idx]) throw std::runtime_error("No unit at this position");
    grid_[idx].reset();
}

Unit* GameField::getUnit(int x, int y) {
    return grid_[index(x, y)].get();
}

const Unit* GameField::getUnit(int x, int y) const {
    return grid_[index(x, y)].get();
}

void GameField::fillWithFactory(const UnitFactory& factory, std::size_t count) {
    for (std::size_t i = 0; i < count; ++i) {
        if (countUnits() >= maxUnits_) return;
        // Ищем свободную клетку
        for (int y = 0; y < height_; ++y) {
            for (int x = 0; x < width_; ++x) {
                if (!grid_[index(x, y)]) {
                    addUnit(factory.createUnit(), x, y);
                    goto next_unit;
                }
            }
        }
        next_unit:;
    }
}

void GameField::clear() {
    for (auto& u : grid_) u.reset();
}