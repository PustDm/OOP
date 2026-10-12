#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include <iterator>
#include "../units/Unit.h"
#include "../factories/UnitFactory.h"

class GameField {
public:
    class Iterator {
    private:
        using BaseIt = std::vector<std::unique_ptr<Unit>>::iterator;
        BaseIt it_;
        BaseIt end_;

        void skipEmpty() {
            while (it_ != end_ && *it_ == nullptr) ++it_;
        }
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = Unit;
        using difference_type   = std::ptrdiff_t;
        using pointer           = Unit*;
        using reference         = Unit&;

        Iterator(BaseIt begin, BaseIt end) : it_(begin), end_(end) { skipEmpty(); }

        Unit& operator*() const { return **it_; }
        Unit* operator->() const { return it_->get(); }

        Iterator& operator++() { ++it_; skipEmpty(); return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        bool operator==(const Iterator& o) const { return it_ == o.it_; }
        bool operator!=(const Iterator& o) const { return it_ != o.it_; }
    };

private:
    int width_;
    int height_;
    std::size_t maxUnits_;
    std::vector<std::unique_ptr<Unit>> grid_; // одномерный массив width*height

    std::size_t index(int x, int y) const {
        if (x < 0 || x >= width_ || y < 0 || y >= height_)
            throw std::out_of_range("Coordinates out of range");
        return static_cast<std::size_t>(y) * width_ + x;
    }

    std::size_t countUnits() const {
        std::size_t n = 0;
        for (const auto& u : grid_) if (u) ++n;
        return n;
    }

public:
    GameField(int width, int height, std::size_t maxUnits);

    GameField(const GameField& other);
    GameField& operator=(const GameField& other);

    GameField(GameField&& other) noexcept;
    GameField& operator=(GameField&& other) noexcept;

    ~GameField() = default;

    void addUnit(std::unique_ptr<Unit> unit, int x, int y);
    void removeUnit(int x, int y);
    Unit* getUnit(int x, int y);
    const Unit* getUnit(int x, int y) const;

    void fillWithFactory(const UnitFactory& factory, std::size_t count);

    int getWidth()  const { return width_;  }
    int getHeight() const { return height_; }
    std::size_t getSize()  const { return countUnits(); }
    std::size_t getMaxUnits() const { return maxUnits_; }

    void clear();

    Iterator begin() { return Iterator(grid_.begin(), grid_.end()); }
    Iterator end()   { return Iterator(grid_.end(),   grid_.end());   }
};