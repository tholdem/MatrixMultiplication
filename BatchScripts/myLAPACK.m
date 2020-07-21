% classdef myLAPACK < coder.LAPACKCallback
%     methods (Static)
%         function hn = getHeaderFilename()
%             hn = 'lapacke.h';
%         end
%         function updateBuildInfo(buildInfo, buildctx)
%             buildInfo.addIncludePaths(fullfile(matlabroot,'extern','include'));
%             libName = 'libmwlapack';
%             libPath = fullfile(matlabroot,'bin','glnxa64');
%             [~,linkLibExt] = buildctx.getStdLibInfo();
%             buildInfo.addLinkObjects([libName linkLibExt], libPath, ...
%                 '', true, true);
%             buildInfo.addDefines('HAVE_LAPACK_CONFIG_H');
%             buildInfo.addDefines('LAPACK_COMPLEX_STRUCTURE');
%             buildInfo.addDefines('LAPACK_ILP64'); 
%         end
%     end
% end

classdef myLAPACK < coder.LAPACKCallback
    methods (Static)
        function hn = getHeaderFilename()
            hn = 'mkl_lapacke.h';
        end
        function updateBuildInfo(buildInfo, buildctx)
            buildInfo.addIncludePaths('/curc/sw/intel/17.4/mkl/include');
            libName = 'libmkl_intel_ilp64';
            libPath = '/curc/sw/intel/17.4/mkl/lib/intel64';
            [~,linkLibExt] = buildctx.getStdLibInfo();
            buildInfo.addLinkObjects([libName linkLibExt], libPath, ...
                '', true, true);
            buildInfo.addDefines('HAVE_LAPACK_CONFIG_H');
            buildInfo.addDefines('LAPACK_COMPLEX_STRUCTURE');
            buildInfo.addDefines('LAPACK_ILP64'); 
        end
    end
end