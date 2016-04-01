# =========================================================================
#  Python wrapper for Ning Ma's optimized gammatone filter C implementation
# -------------------------------------------------------------------------
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
# 
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
# -------------------------------------------------------------------------
#  Paul Michel, ENS LSCP, pmichel31415@gmail.com
# -------------------------------------------------------------------------


from distutils.core import setup, Extension

gammatone = Extension('gammatone',
                    define_macros = [],
                    include_dirs = ['/usr/local/include'],
                    libraries = ['m'],
                    library_dirs = ['/usr/local/lib'],
                    sources = ['gammatonemodule.c'])

setup (name = 'gammatone',
       version = '1.0',
       description = 'Wrapper around Ning Ma\'s gammatone filter optimized C implementation.',
       author = 'Paul Michel',
       author_email = 'pmichel31415@gmail.com',
       url = 'https://github.com/Mandrathax/g',
       ext_modules = [gammatone])
