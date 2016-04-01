from gammatone import gammatone

x=[1.0,2.0,3.0]
fs= 5
cf=0.5
hrect=0

print gammatone(x,fs,cf,hrect)

print gammatone(x,fs,cf)