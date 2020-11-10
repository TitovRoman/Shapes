#include <iostream>

#include "window.h"

std::vector<Window::DrawingId> Window::Draw(std::vector<std::shared_ptr<IDraw>> drawings)
{
    std::vector<DrawingId> result;

    for (auto drawing : drawings)
    {
        result.push_back(Draw(drawing));
    }

    return result;
}

Window::DrawingId Window::Draw(std::shared_ptr<IDraw> drawing)
{
    DrawingId result = current_id_++;
    drawings_[result] = drawing;

    return result;
}

void Window::Print(std::ostream& output_stream_)
{
    Image image(size_);

    for (const auto& [id, drawing_ptr] : drawings_)
    {
        drawing_ptr->Draw(image);
    }

    std::string border = "~ ";
    PrintLine(output_stream_, border, size_.width);
    for (auto& str : image)
    {
        output_stream_ << border;
        for (size_t i = 0; i < str.size(); ++i)
        {
            output_stream_ << str[i] << " ";
        }
        output_stream_ << border << std::endl;
    }
    PrintLine(output_stream_, border, size_.width);
}

void Window::PrintLine(std::ostream& output_stream_,
    std::string border, int len)
{
    output_stream_ << border;
    for (int i = 0; i < len; ++i)
    {
        output_stream_ << border;
    }
    output_stream_ << border << std::endl;
}

