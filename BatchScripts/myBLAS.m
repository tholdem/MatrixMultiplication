% classdef myBLAS < coder.BLASCallback
%     methods (Static)
%         function updateBuildInfo(buildInfo, ~)
%             libPath = '/curc/sw/intel/16.0.3/mkl/lib/intel64';
%             libPriority = '';
%             libPreCompiled = true;
%             libLinkOnly = true;
%             libs = {'libmkl_intel_ilp64' 'libmkl_intel_thread' 'libmkl_core'};
%             buildInfo.addLinkObjects(libs, libPath, libPriority, libPreCompiled, ...
%                                   libLinkOnly);
%             buildInfo.addLinkObjects('libiomp5','/curc/sw/intel/16.0.3/lib/intel64', libPriority, libPreCompiled, libLinkOnly);
%             buildInfo.addIncludePaths('/curc/sw/intel/16.0.3/mkl/include');
%             buildInfo.addDefines('-DMKL_ILP64');
%         end
%         function headerName = getHeaderFilename()
%             headerName = 'mkl_cblas.h';
%         end
%         function intTypeName = getBLASIntTypeName()
%             intTypeName = 'MKL_INT';
%         end
%     end
% end

classdef myBLAS < coder.BLASCallback
    methods (Static)
        function updateBuildInfo(buildInfo, ~)
            % TODO: Update this to point at your MKL include directory
            libPath = '/curc/sw/intel/17.4/mkl/lib/intel64';
            buildInfo.addLinkFlags(['-L' libPath]);
            % TODO: Update this to point to libiomp shipped with MKL
            buildInfo.addLinkFlags(['-L/curc/sw/intel/17.4/lib/intel64 -liomp5']);
            buildInfo.addLinkFlags('-lmkl_intel_ilp64 -lmkl_intel_thread -lmkl_core -lpthread');

            % TODO: Update this to point at your MKL include directory
            buildInfo.addIncludePaths('/curc/sw/intel/17.4/mkl/include');
            buildInfo.addCompileFlags('-DMKL_ILP64');
        end
        function headerName = getHeaderFilename()
            headerName = 'mkl_cblas.h';
        end
        function intTypeName = getBLASIntTypeName()
            intTypeName = 'MKL_INT';
        end
    end
end