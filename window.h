#pragma once

#include <memory>
#include <vector>
#include <map>

#include "utilities.h"
#include "shape.h"


class Window
{
public:
    using DrawingId = size_t;

    void SetSize(Size size)
    {
        size_ = size;
    }

    Size GetSize() const
    {
        return size_;
    }

    std::vector<DrawingId> Draw(std::vector<std::shared_ptr<IDraw>> drawings);

    DrawingId Draw(std::shared_ptr<IDraw> drawing);

    void Print(std::ostream& output_stream_);

private:
    std::map<DrawingId, std::shared_ptr<IDraw>> drawings_;
    DrawingId current_id_ = 0;
    Size size_ = {};

    void PrintLine(std::ostream& output_stream_, std::string border, int len);
};
