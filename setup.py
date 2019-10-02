## ! DO NOT MANUALLY INVOKE THIS setup.py, USE CATKIN INSTEAD

from distutils.core import setup
from catkin_pkg.python_setup import generate_distutils_setup

# fetch values from package.xml
setup_args = generate_distutils_setup(
    packages=['ros2ppm'],
    package_dir={'': 'src'},
    requires=['rcvip_msgs', 'rospy', 'rosserial_arduino']
)

setup(**setup_args)
