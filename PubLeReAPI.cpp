#include "pybind11/include/pybind11/pybind11.h"
#include "Motor.h"
#include "ColorSensor.h"
#include "TouchSensor.h"

namespace py = pybind11;

PYBIND11_MODULE(legoapi, m) {
    m.doc() = "";

	py::class_<Motor>(m,"Motor")
		.def(py::init<Output>())
		.def("angle",&Motor::angle)
		.def("reset_angle",&Motor::reset_angle)
		.def("brake",&Motor::brake)
		.def("run",&Motor::run)
		.def("run_time",&Motor::run_time)
		.def("run_angle",&Motor::run_angle)
		.def("run_target",&Motor::run_target);

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

	py::enum_<Then>(m, "Then", py::arithmetic())
        .value("Brake", Then::Brake)
		.value("Coast", Then::Coast)
		.value("Hold", Then::Hold);

	py::class_<ColorSensor>(m,"ColorSensor")
		.def(py::init<Input>())
		.def("ambient",&ColorSensor::ambient);

	py::class_<TouchSensor>(m,"TouchSensor")
		.def(py::init<Input>())
		.def("pressed",&TouchSensor::pressed);

}