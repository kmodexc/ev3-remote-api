#include "../pybind11/include/pybind11/pybind11.h"
#include "Motor.h"
#include "ColorSensor.h"
#include "TouchSensor.h"
#include "UltrasonicSensor.h"

namespace py = pybind11;

PYBIND11_MODULE(legoapi, m) {
    m.doc() = "einsteinmaster.github.io";

	py::class_<Motor>(m,"Motor")
		.def(py::init<Port>())
		.def("angle",&Motor::angle)
		.def("reset_angle",&Motor::reset_angle)
		.def("brake",&Motor::brake)
		.def("run",&Motor::run)
		.def("run_time",&Motor::run_time)
		.def("run_angle",&Motor::run_angle)
		.def("run_target",&Motor::run_target);

	py::enum_<Port>(m, "Port", py::arithmetic())
        .value("S1", Port::S1)
		.value("S2", Port::S2)
		.value("S3", Port::S3)
        .value("S4", Port::S4)
		.value("A", Port::A)
		.value("B", Port::B)
		.value("C", Port::C)
		.value("D", Port::D)
		.value("E", Port::E)
		.value("F", Port::F);

	py::enum_<Then>(m, "Then", py::arithmetic())
        .value("Brake", Then::Brake)
		.value("Coast", Then::Coast)
		.value("Hold", Then::Hold);

	py::class_<ColorSensor>(m,"ColorSensor")
		.def(py::init<Port>())
		.def("ambient",&ColorSensor::ambient);

	py::class_<TouchSensor>(m,"TouchSensor")
		.def(py::init<Port>())
		.def("pressed",&TouchSensor::pressed);

	py::class_<UltrasonicSensor>(m,"UltrasonicSensor")
		.def(py::init<Port>())
		.def("distance",&UltrasonicSensor::distance);

}