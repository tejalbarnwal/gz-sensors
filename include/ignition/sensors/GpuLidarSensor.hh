/*
 * Copyright (C) 2018 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef IGNITION_SENSORS_GPULIDARSENSOR_HH_
#define IGNITION_SENSORS_GPULIDARSENSOR_HH_

#include <string>
#include <vector>
#include <memory>
#include <sstream>

#include <sdf/sdf.hh>

#include <ignition/common/Time.hh>
#include <ignition/common/Timer.hh>
#include <ignition/common/Console.hh>
//#include <ignition/common/Exception.hh>
#include <ignition/common/Mesh.hh>
#include <ignition/common/MeshManager.hh>
#include <ignition/common/PluginMacros.hh>

#include <ignition/sensors/Sensor.hh>
#include <ignition/sensors/Export.hh>
#include <ignition/sensors/Lidar.hh>
//#include <ignition/sensors/ign_sensors_gpu_lidar_export.hh>

#include <ignition/msgs.hh>

#include <ignition/math/Color.hh>
#include <ignition/math/Helpers.hh>
#include <ignition/math/Pose3.hh>
#include <ignition/math/Vector3.hh>
#include <ignition/math/Angle.hh>

#include <ignition/rendering/GpuRays.hh>

/*
#ifndef _WIN32
  #include <dirent.h>
#else
  // Ensure that Winsock2.h is included before Windows.h, which can get
  // pulled in by anybody (e.g., Boost).
  #include <Winsock2.h>
  #include "gazebo/common/win_dirent.h"
#endif
*/


namespace ignition
{
  namespace sensors
  {
    /// \brief forward declarations
    class GpuLidarSensorPrivate;

    /// \brief GpuLidar Sensor Class
    ///
    ///   This class creates laser scans using the GPU. It's measures the range
    ///   from the origin of the center to points on the visual geometry in the
    ///   scene.
    ///
    ///   It offers both an ignition-transport interface and a direct C++ API
    ///   to access the image data. The API works by setting a callback to be
    ///   called with image data.
    class IGNITION_SENSORS_VISIBLE GpuLidarSensor : public Lidar
    {
      /// \brief constructor
      public: GpuLidarSensor();

      /// \brief destructor
      public: virtual ~GpuLidarSensor();

      /// \brief Force the sensor to generate data
      /// \param[in] _now The current time
      /// \return true if the update was successfull
      public: virtual bool Update(const common::Time &_now) override;

      /// \brief Initialize values in the sensor
      /// \return True on success
      public: virtual bool Init() override;

      /// \brief Create Lidar sensor
      public: virtual bool CreateLidar() override;

      /// \brief Gets the camera count
      /// \return Number of cameras
      public: unsigned int CameraCount() const;

      /// \brief Gets if sensor is horizontal
      /// \return True if horizontal, false if not
      public: bool IsHorizontal() const;

      public: void SetScene(ignition::rendering::ScenePtr _scene);

      public:void RemoveGpuRays(ignition::rendering::ScenePtr _scene);

      public: ignition::rendering::GpuRaysPtr GpuRays() const;

      public: virtual bool Load(sdf::ElementPtr _sdf);
      /// \brief Return the ratio of horizontal ray count to vertical ray
      /// count.
      ///
      /// A ray count is the number of simulated rays. Whereas a range count
      /// is the total number of data points returned. When range count
      /// != ray count, then values are interpolated between rays.
      public: double RayCountRatio() const;

      /// \brief Get the horizontal field of view of the laser sensor.
      /// \return The horizontal field of view of the laser sensor.
      public: ignition::math::Angle HFOV() const;

      /// \brief Get the vertical field-of-view.
      /// \return Vertical field of view.
      public: ignition::math::Angle VFOV() const;

      public: virtual ignition::common::ConnectionPtr ConnectNewLidarFrame(
          std::function<void(const float *_scan, unsigned int _width,
                  unsigned int _heighti, unsigned int _channels,
                  const std::string &/*_format*/)> _subscriber) override;

      /// \brief Data pointer for private data
      /// \internal
      public: std::unique_ptr<GpuLidarSensorPrivate> gpuLidarDataPtr;
    };
  }
}

#endif

