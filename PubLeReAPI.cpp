#include "pybind11/include/pybind11/pybind11.h"
#include "Brick.h"

namespace py = pybind11;

PYBIND11_MODULE(legoapi, m) {
    m.doc() = "";

	py::class_<Brick>(m,"Brick")
		.def(py::init())
		.def("Initialize",&Brick::Initialize)
		.def("setMotorPower",&Brick::setMotorPower)
		.def("getSensorVal",&Brick::getSensorVal);

	py::enum_<Input>(m, "Input", py::arithmetic())
        .value("Port1", Input::Port1)
		.value("Port2", Input::Port2)
		.value("Port3", Input::Port3)
        .value("Port4", Input::Port4);

	py::enum_<Output>(m, "Output", py::arithmetic())
        .value("A", Output::A)
		.value("B", Output::B)
		.value("C", Output::C)
        .value("D", Output::D);
}