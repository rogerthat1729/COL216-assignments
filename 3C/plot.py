import pandas as pd
import plotly.graph_objects as go

df = pd.read_csv('output.csv')
df = df[df['Size'] % 256 != 0]
df1 = df[['Size', 'MultiplyTime1']]
df2 = df[['Size', 'MultiplyTime2']]
df3 = df[['Size', 'MultiplyTime3']]
df4 = df[['Size', 'MultiplyTime4']]
df5 = df[['Size', 'MultiplyTime5']]
df6 = df[['Size', 'MultiplyTime6']]

fig = go.Figure()

fig.add_trace(go.Scatter(x=df1['Size'], y=df1['MultiplyTime1'], mode='lines', name='ijk'))
fig.add_trace(go.Scatter(x=df2['Size'], y=df2['MultiplyTime2'], mode='lines', name='ikj'))
fig.add_trace(go.Scatter(x=df3['Size'], y=df3['MultiplyTime3'], mode='lines', name='kji'))
fig.add_trace(go.Scatter(x=df4['Size'], y=df4['MultiplyTime4'], mode='lines', name='kij'))
fig.add_trace(go.Scatter(x=df5['Size'], y=df5['MultiplyTime5'], mode='lines', name='jki'))
fig.add_trace(go.Scatter(x=df6['Size'], y=df6['MultiplyTime6'], mode='lines', name='jik'))

fig.show()