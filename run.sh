./project.sh clean
./project.sh makeall
./project.sh insmod
./project.sh rmmod

sudo test/service_manager &
sudo test/test_server &
sudo test/test