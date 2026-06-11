#include <string>
#include <fstream>
#pragma cling add_include_path("/usr/local/include/opencv4")
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#include "nlohmann/json.hpp"
#include "xtl/xbase64.hpp"
#include <Python.h>

namespace nl = nlohmann;
namespace plt = matplotlibcpp;

namespace im
{
    struct image
    {
        inline image(const std::vector<uchar>& buffer)
        {
            m_buffer.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
        }
        std::stringstream m_buffer;
    };
    
    nl::json mime_bundle_repr(const image& i)
    {
        nl::json bundle = nl::json::object();
        bundle["image/png"] = xtl::base64encode(i.m_buffer.str());
        return bundle;
    } 
}



im::image displayImage(const cv::Mat& image)
{
    cv::Mat displayMat;

    if (image.channels() == 1)
    {
        cv::cvtColor(image, displayMat, cv::COLOR_GRAY2BGR);
    }
    else
    {
        displayMat = image;
    }

    // draw into matplotlib figure
    plt::imshow(displayMat);

    // capture matplotlib canvas
    PyObject* pyplot = PyImport_ImportModule("matplotlib.pyplot");

    PyObject* ioModule = PyImport_ImportModule("io");
    PyObject* bytesIOClass = PyObject_GetAttrString(ioModule, "BytesIO");
    PyObject* bufferObj = PyObject_CallObject(bytesIOClass, nullptr);

    PyObject* savefigFunc = PyObject_GetAttrString(pyplot, "savefig");

    PyObject* args = PyTuple_Pack(1, bufferObj);

    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "format", PyUnicode_FromString("png"));
    // PyDict_SetItemString(kwargs, "bbox_inches", PyUnicode_FromString("tight"));

    PyObject_Call(savefigFunc, args, kwargs);

    PyObject* getvalue = PyObject_GetAttrString(bufferObj, "getvalue");
    PyObject* bytes = PyObject_CallObject(getvalue, nullptr);

    char* data = nullptr;
    Py_ssize_t size = 0;

    PyBytes_AsStringAndSize(bytes, &data, &size);

    std::vector<unsigned char> pngBuffer(data, data + size);

    Py_DECREF(bytes);
    Py_DECREF(getvalue);
    Py_DECREF(kwargs);
    Py_DECREF(args);
    Py_DECREF(savefigFunc);
    Py_DECREF(bufferObj);
    Py_DECREF(bytesIOClass);
    Py_DECREF(ioModule);
    Py_DECREF(pyplot);

    return im::image(pngBuffer);
}

im::image displayImage()
{
    // capture matplotlib canvas
    PyObject* pyplot = PyImport_ImportModule("matplotlib.pyplot");

    PyObject* ioModule = PyImport_ImportModule("io");
    PyObject* bytesIOClass = PyObject_GetAttrString(ioModule, "BytesIO");
    PyObject* bufferObj = PyObject_CallObject(bytesIOClass, nullptr);

    PyObject* savefigFunc = PyObject_GetAttrString(pyplot, "savefig");

    PyObject* args = PyTuple_Pack(1, bufferObj);

    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "format", PyUnicode_FromString("png"));
    // PyDict_SetItemString(kwargs, "bbox_inches", PyUnicode_FromString("tight"));

    PyObject_Call(savefigFunc, args, kwargs);

    PyObject* getvalue = PyObject_GetAttrString(bufferObj, "getvalue");
    PyObject* bytes = PyObject_CallObject(getvalue, nullptr);

    char* data = nullptr;
    Py_ssize_t size = 0;

    PyBytes_AsStringAndSize(bytes, &data, &size);

    std::vector<unsigned char> pngBuffer(data, data + size);

    Py_DECREF(bytes);
    Py_DECREF(getvalue);
    Py_DECREF(kwargs);
    Py_DECREF(args);
    Py_DECREF(savefigFunc);
    Py_DECREF(bufferObj);
    Py_DECREF(bytesIOClass);
    Py_DECREF(ioModule);
    Py_DECREF(pyplot);

    return im::image(pngBuffer);
}