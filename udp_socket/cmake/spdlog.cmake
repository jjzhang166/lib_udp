
#-------------------------------------------------------------------
include(fetchcontent)
 fetchcontent_declare(	spdlog	#������
						GIT_REPOSITORY https://gitee.com/mohistH/spdlog.git	# �ֿ��ַ
						GIT_TAG v1.x # ��汾
						SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/spdlog # ָ�������ص�ַ
						)

fetchcontent_makeavailable(spdlog)
