
# SubDir=$(shell ls -l |grep ^d | awk '{print $$9}')
# SubDir=$(shell ls -l |grep ^d | grep var_start |awk '{print $$9}')
SubDir=var_start


all:
	$(foreach var, $(SubDir), make -C $(var))

# clean:
# 	$(foreach var, $(SubDir), make -C $(var) clean)

clean:
	@for dir in $(SubDir); \
	do make -C $$dir clean;\
	done
